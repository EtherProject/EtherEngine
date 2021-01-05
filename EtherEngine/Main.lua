UsingMoudle("Window")
UsingMoudle("Graphic")
UsingMoudle("Interactivity")

CreateWindow("TestWindow", {x = WINDOW_POSITION_DEFAULT, y = WINDOW_POSITION_DEFAULT, w = 1280, h = 720}, {})

-- hsla = RGBAToHSLA({r = 125, g = 36, b = 75, a = 100})
-- print(hsla.h, hsla.s, hsla.l, hsla.a)

-- response = RequestGet("https://www.baidu.com/")
-- print(response.status)
-- print(response.body)
-- for key, value in pairs(response.headers) do
--     print(key, value)
-- end

while true do

    SetDrawColor({r = 30, g = 30, b = 30, a = 255})
    ClearWindow()

    SetDrawColor({r = 255, g = 255, b = 0, a = 255})
    FillRectangle({x = 0, y = 0, w = 200, h = 150})

    if UpdateEvent() then
        local _event = GetEventType()
        if _event == EVENT_QUIT then
            break
        elseif _event == EVENT_WINDOW_MOVE then
            
        end
    end

    UpdateWindow()
end