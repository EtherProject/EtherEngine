# Good Journey Quick Start

[简体中文](quick-start.md) | English | [日本語](quick-start_ja.md)

> The 4.x version quick start document is under maintenance. Please read the [Full Manual](README.md) or use the 3.x version.

Welcome to EtherAPI (for EtherEngine). EtherAPI consists of a set of lightweight Lua game development interfaces developed based on many C/C++ open source projects for game developers to quickly build game prototypes or conduct various conceptual tests. similarly, it also supports various games (The current version only supports 2D games) in development and production environments.

Here is a quick start guide for EtherAPI, its purpose is to help you quickly get started using the interface library; therefore, this document will only introduce the content of commonly used interfaces, and many important functions will only be briefly introduced or even not mentioned. For more complete information, you should read [Full EtherAPI Manual](README.md).

---

## Launching

The EtherAPI launcher will automatically load the `config.json` as a configuration file, the configuration file describes various information such as the entry file and add in path. A possible configuration file is as follows:

```json
{
    "entry": "scripts/Main.lua",
    "package": {
        "path": [
            "scripts/?.lua",
            "modules/?.lua"            
        ],
        "cpath": [
            "modules/?.dll"
        ]
    },
    "command": [
        "--debug"
    ]
}
```

For more information, see [Complete Manual: Configuration](README.md#Configuration).

---



## Importing Modules

In order to facilitate namespace management and optimize the speed of the engine, we have given the developer the authority to enable the specified module. Developers can enable the module with the specified name through the `UsingModule()` function. The supported module name parameters are shown in [Complete Manual : Directory](README.md#directory), special, the incoming string `All` means that the engine will enable all modules, and this method can be used to avoid cumbersome package guide code during testing. In addition, unless these modules are The included API will be needed in the program, we do not recommend you to do this.

Differing from the  Lua's standard library function `require()`, the function `UsingModule()` does not return the table type module as the return value, but pushes the functions contained in the specified module into the global space. The return value is `nil`. It should be noted that in the versions of the `UsingModule()` function supported by EtherAPI 3.0.x and below, the introduction of the module will introduce the macros contained in the module into the global space, while in EtherAPI 3.0.x and above, `UsingModule( )` The function puts the macro into the global table with the same name as the module. The relevant difference sample code is as follows:

```lua
-- below the version of 3.0

UsingModule("Window")

CreateWindow(
    "HelloWorld",
    {x = 0, y = 0, w = 1280, h = 720},
    {WINDOW_RESIZABLE, WINDOW_MAXIMIZED}
)

-- above the version of 3.0

UsingModule("Window")

CreateWindow(
    "HelloWorld",
    {x = 0, y = 0, w = 1280, h = 720},
    {Window.WINDOW_RESIZABLE, Window.WINDOW_MAXIMIZED}
)

```

The so called `Macro` in EtherAPI is essentially a variable of type number, which is often used as a function parameter to represent the sign of the specified meaning.



---



## Creating Window(s)

The API `CreateWindow()` in the `Window` module can help us easily create a game window and use this window as a context for subsequent drawing and rendering.

The `CreateWindow()` function accepts three parameters for initializing window properties:

+ The first parameter is the window title of string type
+ The second parameter is a rectangular structure of table type to describe the position and size of the window
+ The third parameter is the table type window identifier, which is used to describe meta-information such as the style of the window

Here we mentioned the concept of `rectangular structure`, similar to `dot structure`, `RGBA color space structure` and `HSLA color space structure`, their essence is a table variable containing a specific key value, For example, in the `rectangular structure`, the keys that need to be included are `x`, `y`, `w` and `h`, which are used to represent the coordinates (top left vertex position) and size of a certain rectangular area, and The `dot structure` only needs to include the two key values `x` and `y`. For more information, see [Complete Manual: Appendix](README.md#Appendix).

Therefore, creating a stretchable window with the title `HelloWorld` and displayed in the default position can be written as the following code:

```lua
-- import window
UsingModule("Window")

-- Create a resizable window of 1280 x 720
-- using the title "HelloWorld" and show on default position (usually on the middle of the screen)
CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)

-- dive into loop
while true do end
```

Since EtherAPI does not provide the main loop of the game, if you perform other operations after the window is created, the window will automatically close after the program exits. You can prevent the window from exiting through [Event Loop](#Event Interactive). A commonly used method during game development.



---



## Rendering

The "Graphic" module provides operations related to image rendering. It should be noted that these operations are based on the windows created above, so if you call some APIs without creating a window, it may cause the engine to report an error (Debug Mode Next) or unexpected results (in release mode). .

### Rendering Images

The most common operation in the game is to load and draw pictures, so EtherAPI provides a set of extremely concise and efficient interfaces:

+ First, the `LoadImage()` function is responsible for loading the image file from the hard disk to the memory. Its parameter is the image file path of string type, and the return value is userdata of Image type. If the image fails to load in Debug mode, the engine will report an error. .

+ Then, use the `CreateTexture()` function to render the Image data returned in the previous step into texture data that can be displayed, and return the userdata of the Texture type. If the texture fails to be created in Debug mode, it will cause the engine to report an error.

+ Finally, the `CopyTexture()` function can copy the texture created in the previous step to the rendering buffer. This function accepts two parameters, namely the userdata of the Texture type and a description of the position of the image in the window coordinate system and The size of the rectangular structure. It should be noted that the `CopyTexture()` function just copies the texture data to the rendering buffer, but does not actually refresh the display on the screen, so we need to call `UpdateWindow in the `Window` module in the next step ()` function to display the contents of the rendering buffer on the screen.

In other words, only a few lines of code as follows can display the picture:

```lua
-- importing Window and Graphic module
UsingModule("Window")
UsingModule("Graphic")

-- creating window
CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)

-- loading Player.png
image = LoadImage("Player.png")

-- convert into texture
texture = CreateTexture(image)

-- copying into buffer
CopyTexture(texture, {x = 0, y = 0, w = 1280, h = 720})

while true do
    -- do update on window
    UpdateWindow() 
end
```

What needs to be clear is that in the window coordinate system, the origin of the coordinate system is located at the upper left corner of the window, the horizontal direction to the right is the positive direction of the x axis, and the vertical direction downward is the positive direction of the y axis.

In addition, if you need to crop or revolve the image for display, you only need to call the specified function when copying the texture to the rendering buffer, such as:

+ [`CopyReshapeTexture()`](Graphic/CopyReshapeTexture.md) function can crop the texture first and then copy
+ [`CopyRotateTexture()`](Graphic/CopyReshapeTexture.md) function can first rotate the texture and then copy
+ [`CopyRotateReshapeTexture()`](Graphic/CopyReshapeTexture.md) function will rotate and crop the texture before copying

For descriptions of these functions, see [Manual: Graphic Module](Graphic/README.md)



### Rendering Text

Stuff like that, if you want to render text content to the screen, you also need to perform steps similar to displaying pictures. All text content that needs to be displayed needs to be rendered as a text texture before it can be displayed on the screen. The specific steps are as follows:

+ First, you need to use the `LoadFont()` function to load the font file into the memory. The first parameter required by the function is the path of the font file. Since a font file may contain multiple fonts of different sizes, it must Use the second parameter to specify the font size index we need; similar to the `LoadImage()` function, for example, the function will return Font type userdata, if the load fails in Debug mode, it will cause the engine to report an error.

+ Secondly, use text texture rendering functions such as `CreateTextImageBlended()` to render the text string as userdata of type Image and return it. `CreateTextImageBlended()` accepts three parameters, namely font data of userdata type and string type The text content and the RGBA color space structure used to describe the font color.

+ Finally, the same as the last two steps of displaying the picture, you only need to create a texture with the `CreateTexture()` function and copy the texture with the `CopyTexture()` function to complete the entire process of text rendering.

The sample code is as follows:

```lua
UsingModule("Window")
UsingModule("Graphic")

-- creating wondow
CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)

-- loading font file(ttf)
font = LoadFont("GameFont.ttf", 50)

-- convert into renderable material
text_image = CreateTextImageBlended(
    font,
    "This is My-Game!",
    -- set color red
    {r = 255, g = 0, b = 0, a = 255}
)

-- convert into texture
text_texture = CreateTexture(text_image)

-- copying into buffer
CopyTexture(text_texture, {x = 0, y = 0, w = 1280, h = 720})

while true do
    -- do update on window
    UpdateWindow() 
end
```

In the second step of rendering text maps, there are many functions that support different text rendering methods and different text encoding formats; in addition, developers can also use such as [`SetFontStyle()`](Graphic/SetFontStyle.md) and other functions to set the font style. For more details, please refer to [Manual: Graphic Module](Graphic/README.md)



### Drawing Graphics

EtherAPI also provides a large number of geometric drawing APIs, such as the drawing functions of basic geometric primitives such as points, lines, rectangles, triangles and circles, as well as the drawing of their filled graphics. The sample code is as follows:

```lua
UsingModule("Window")
UsingModule("Graphic")

-- creating wondow
CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)

-- set window default draWing color to red
SetDrawColor({r = 255, g = 0, b = 0, a = 255})

-- Draw a hollow circle with a radius of 25 pixels in the center of the screen
Circle({x = 640, y = 360}, 25)

-- set window default draWing color to blue
SetDrawColor({r = 0, g = 0, b = 255, a = 255})

-- Draw a filled rectangle with 50 pixels in length and width in the upper left corner of the screen
FillRectangle({x = 0, y = 0, w = 50, h = 50})

while true do
    -- do update on window
    UpdateWindow() 
end
```

The drawing color of the window can be set by the `SetDrawColor()` function. All subsequent drawing of geometric primitives will use this color as the drawing color and filling color.

It should be noted that all geometric drawing is also performed in the rendering buffer, so after the drawing process is completed, you still need to call the `UpdateWindow()` function to flush the buffer.

For more details about the geometric drawing API, please refer to [Manual: Graphic Module](Graphic/README.md)



---



## Media control

Sound is an indispensable part of the game. EtherAPI also provides a nearly perfect implementation: the sound in EtherAPI is divided into two types: `music` and `sound effects`. Music is often used as a global background sound; sound effects are used for Ambient sounds for battles, actions, etc. To some extent, music and sound effects are equivalent and interchangeable, but the memory loading strategy and broadcast control API for the two may be different.

All sounds are played asynchronously, so we don’t need to worry that the playing of music and sound effects will block the main thread of the game, but it should be noted that if the program does not perform an event loop to ensure that the program continues to run, the program ends and exits. Then the music will stop playing (similar to the automatic exit of the above-mentioned window)

The following is a simple sample code for media playback:

```lua
-- importing module Media
UsingModule("Media")

-- load music file BGM.mp3
music = LoadMusic("BGM.mp3")

-- Use the fade-in effect to play music in a loop, the duration of the fade-in effect is 1.5 seconds
FadeInMusic(music, -1, 1500)

-- dive into loop
while true do end
```

For more media broadcast control API, please refer to [Manual: Media Module](Media/README.md)



---



# Interactive

Interactivity is an important part of the game. The `Interactivity` module of EtherAPI provides a simple and lightweight interactive event processing mechanism. Commonly used event interactive processing APIs are as follows:

+ [`UpdateEvent()`](Interactivity/UpdateEvent.md): Update the event queue. If there is a new unprocessed event in the current event queue, it will return `true`, otherwise it will return `false`.
+ [`GetEventType()`](Interactivity/GetEventType.md): Get the unprocessed event type of the event queue.
+ [`GetCursorPosition()`](Interactivity/GetCursorPosition.md): Get the current mouse position, the return value is a point structure describing the mouse position in the current window coordinate system.
+ [`GetScrollValue()`](Interactivity/GetScrollValue.md): Get the scrolling distance of the mouse wheel. The return value is the horizontal scrolling distance and the vertical scrolling distance.

Therefore, a general event loop can be written as the following code:

```lua
UsingModule("Interactivity")

-- creating window
CreateWindow(
    "HelloWorld",
    {
        x = Window.WINDOW_POSITION_DEFAULT, 
        y = Window.WINDOW_POSITION_DEFAULT, 
        w = 1280, 
        h = 720
    },
    {
        Window.WINDOW_RESIZABLE,
        Window.WINDOW_MAXIMIZED
    }
)

while true do
    -- Update the event category, if there is an unprocessed event, perform partition judgment processing
    if UpdateEvent() then
        -- Get the current unprocessed event type
        local _event = GetEventType()
        -- If the event type is an exit event, it will jump out of the main loop of the game
        -- The macro usage method here only applies to 3.0.x and above
        if _event == Interactivity.EVENT_QUIT then
            break
        -- If the event type is a mouse movement event, output the current mouse position
        -- The macro usage method here only applies to 3.0.x and above
        elseif _event == Interactivity.EVENT_MOUSEMOTION then
            local _cursor_pos = GetCursorPosition()
            print("CursorPosition: ", _cursor_pos.x, _cursor_pos.y)
        end
    end

    -- do update on window
    UpdateWindow() 
end
```

In general, if a window does not continuously receive and update events, it will be considered by the system to enter an abnormal `unresponsive` state. Obviously, since this window will not respond to events, it cannot be dragged. , Minimize or close the window; therefore, it is necessary to keep calling the `UpdateEvent()` function in the main loop of the game.

For more interactive event types, please refer to [Manual：Interactivity](Interactivity/appendix.md)



---



## Other Tools

Tool module is a kind of module that encapsulates algorithm and system level to assist game development. It covers algorithm, network, time, JSON parsing, string encoding, operating system and other modules. Only its catalog index is placed below. It will be introduced in detail, please refer to the corresponding part of the [full manual](README.md#directory) for specific content:

+ [Algorithm module](Algorithm/README.md): encapsulates common algorithms such as numerical limitation, basic collision detection, color space conversion, etc.
+ [Network Module](Network/README.md): Provides operations such as host address and routing separation, HTTP request, etc.
+ [Time Module](Time/README.md): Covers functions such as program pause, delay, dynamic delay, high-resolution timing, etc.
+ [JSON Module](JSON/README.md): Provides JSON format data encoding and decoding operations
+ [String Module](String/README.md): Provides a convenient operation for converting between different coded strings
+ [Operating System Module](OS/README.md): encapsulates functions such as system information acquisition, platform-related file system API, clipboard operation, etc.



---



## License

EtherAPI is released under the MIT license agreement

```
MIT License

Copyright (c) 2020 Voidmatrix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

