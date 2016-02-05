local events = {}

local client_command_listeners = {}
function events.OnClientCommand(callback)
  table.insert(client_command_listeners, callback)
end

function events.FireClientCommand(client, args)
  for idx = 1, table.getn(events.client_command) do
    success, msg = pcall(events.client_command[idx], client, args)
    if not success then
      print(msg)
    end
  end
end

return events
