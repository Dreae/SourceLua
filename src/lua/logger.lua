Logger = {}

function Logger:new(file)
  newObj = {
    logFile = io.open(file, 'w')
  }
  newObj.logFile:setvbuf("line")

  self.__index = self
  return setmetatable(newObj, self)
end

function Logger:info(msg)
  self.logFile:write(string.format("L %s :: [INFO] %s\n", os.date("%D - %H:%M:%S"), msg))
end

function Logger:warn(msg)
  self.logFile:write(string.format("L %s :: [WARN] %s\n", os.date("%D - %H:%M:%S"), msg))
end

function Logger:error(msg)
  self.logFile:write(debug.traceback(string.format("L %s :: [ERROR] %s", os.date("%D - %H:%M:%S"), msg), 2))
  self.logFile:flush()
end

return Logger
