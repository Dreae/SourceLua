local server = {}

local cmds = {}
function server.RegClientCmd(name, callback)
  cmds[name] = callback
end

function dispatchClientCommand(client, args)
  cmds[args[1]](client, args)
end

SourceLua.Events.OnClientCommand(dispatchClientCommand)

return server
