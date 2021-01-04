CreateWindow("TestWindow", {x = WINDOW_POSITION_DEFAULT, y = WINDOW_POSITION_DEFAULT, w = 640, h = 480}, {})

-- hsla = RGBAToHSLA({r = 125, g = 36, b = 75, a = 100})
-- print(hsla.h, hsla.s, hsla.l, hsla.a)

response = RequestGet("https://www.baidu.com/")
print(response.status)
print(response.body)
for key, value in pairs(response.headers) do
    print(key, value)
end

while true do

    ClearWindow()

    if UpdateEvent() then
        local _event = GetEventType()
        if _event == EVENT_QUIT then
            break
        elseif _event == EVENT_WINDOW_MOVE then
            
        end
    end

    UpdateWindow()
end