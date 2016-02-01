local events = {
  client_command = { }
}

function events.OnClientCommand(callback)
  table.insert(events.client_command, callback)
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
