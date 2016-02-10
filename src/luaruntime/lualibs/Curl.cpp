#include "luaruntime/lualibs/Curl.hpp"
#include "luaruntime/LuaRuntime.hpp"
#include "GameHooks.hpp"

LuaCurl g_LuaCurl;

size_t curl_read_cb(char *ptr, size_t size, size_t nmemb, void *userdata) {
  CurlReq *req = (CurlReq *)userdata;
  size_t newDataSize = size * nmemb;
  if(req->dataSize + newDataSize > req->bufferSize) {
    size_t newSize = req->dataSize + newDataSize + (CURL_MAX_WRITE_SIZE / 2);
    char *buffer = (char *)malloc(newSize);
    memcpy(buffer, req->data, req->dataSize);

    free(req->data);
    req->data = buffer;
    req->bufferSize = newSize;
  }

  memcpy(&req->data[req->dataSize], ptr, newDataSize);
  req->dataSize = req->dataSize + newDataSize;
  return newDataSize;
}

void LuaCurl::OnPluginStart() {
  curl_global_init(CURL_GLOBAL_DEFAULT);
  g_GameHooks.AddFrameHook([this](bool simulating) -> void {
    this->OnGameFrame(simulating);
  });
}

void LuaCurl::OnGameFrame(bool simulating) {
  if(mCurlHandle) {
    curl_multi_perform(mCurlHandle, &this->running_handles);

    int msgs = 0;
    CURLMsg *m = curl_multi_info_read(mCurlHandle, &msgs);
    if(m && (m->msg == CURLMSG_DONE)) {
      CURL *transfer = m->easy_handle;
      curl_multi_remove_handle(mCurlHandle, transfer);
      CurlReq *req;

      curl_easy_getinfo(transfer, CURLINFO_PRIVATE, (char **)&req);
      lua_rawgeti(g_LuaRuntime.L, LUA_REGISTRYINDEX, req->callbackRef);
      lua_pushlstring(g_LuaRuntime.L, req->data, req->dataSize);
      lua_docall(g_LuaRuntime.L, 1, 0);

      free(req->data);
      if(req->headers) {
        curl_slist_free_all(req->headers);
      }

      free(req);

      curl_easy_cleanup(transfer);
    }

    if(running_handles == 0) {
      curl_multi_cleanup(mCurlHandle);
    }
  }
}

void LuaCurl::Get(const char *url, CurlReq *req) {
  if(!mCurlHandle) {
    mCurlHandle = curl_multi_init();
  }

  CURL *transfer = curl_easy_init();
  curl_easy_setopt(transfer, CURLOPT_URL, url);
  curl_easy_setopt(transfer, CURLOPT_WRITEFUNCTION, curl_read_cb);
  curl_easy_setopt(transfer, CURLOPT_WRITEDATA, req);
  curl_easy_setopt(transfer, CURLOPT_PRIVATE, req);

  if(req->headers) {
    curl_easy_setopt(transfer, CURLOPT_HTTPHEADER, req->headers);
  }

  curl_multi_add_handle(mCurlHandle, transfer);
}

void parse_req_options(lua_State *L, CurlReq *req) {
  lua_pushvalue(L, 2);

  lua_getfield(L, -1, "headers");
  if(!lua_isnil(L, -1) && lua_istable(L, -1)) {
    struct curl_slist *headers = NULL;
    lua_pushnil(L);
    while(lua_next(L, -2)) {
      size_t keyLen;
      const char *key = lua_tolstring(L, -2, &keyLen);
      size_t valueLen;
      const char *value = lua_tolstring(L, -1, &valueLen);
      size_t maxLen = keyLen + valueLen + 8;
      char *buffer = (char *)malloc(maxLen);

      g_SMAPI->Format(buffer, maxLen, "%s: %s", key, value);
      headers = curl_slist_append(headers, buffer);

      free(buffer);
      lua_pop(L, 1);
    }

    req->headers = headers;
  }
  lua_remove(L, -1);
}

CurlReq *new_req() {
  CurlReq *req = (CurlReq *)malloc(sizeof(CurlReq));
  req->callbackRef = 0;
  req->dataSize = 0;
  req->bufferSize = CURL_MAX_WRITE_SIZE;
  req->data = (char *)malloc(CURL_MAX_WRITE_SIZE);
  req->headers = NULL;
}

int lua_Curl_Get(lua_State *L) {
  CurlReq *req = new_req();
  if(lua_gettop(L) == 3) {
    parse_req_options(L, req);
    lua_pushvalue(L, 3);
    req->callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);
  } else {
    lua_pushvalue(L, 2);
    req->callbackRef = luaL_ref(L, LUA_REGISTRYINDEX);
  }
  g_LuaCurl.Get(lua_tostring(L, 1), req);

  return 0;
}

void lua_register_Curl(lua_State *L) {
  lua_getglobal(L, "SourceLua");

  lua_newtable(L);
  lua_pushcfunction(L, lua_Curl_Get);
  lua_setfield(L, -2, "Get");

  lua_setfield(L, -2, "Curl");
  lua_remove(L, -1);
}
