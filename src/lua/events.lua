local events = {}

local client_command_listeners = {}
function events.OnClientCommand(callback)
  table.insert(client_command_listeners, callback)
end

function events.FireClientCommand(client, args)
  local max_res = 0
  for idx = 1, table.getn(client_command_listeners) do
    local success, res = pcall(client_command_listeners[idx], client, args)
    if not success then
      print(msg)
    elseif res ~= nil then
      if res == SourceLua.Server.Cmd_Supercede then
        return res
      elseif res > max_res then
        max_res = res
      end
    end
  end
  return max_res
end

return events
