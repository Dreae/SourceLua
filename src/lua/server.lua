local server = {}

local cmds = {}
function server.RegClientCmd(name, callback)
  cmds[name] = callback
end

function dispatchClientCommand(client, args)
  callback = cmds[args[1]]
  if callback ~= nil then
    return callback(client, args)
  end
end

SourceLua.Events.OnClientCommand(dispatchClientCommand)

return server
