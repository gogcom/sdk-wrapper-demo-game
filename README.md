# Steam SDK Wrapper Demo Game (beta)

This is a simple demonstration game using GOG's Steam SDK Wrapper to hijack SteamWorks api calls and translate them to GOG ones.


## Building

Supported Galaxy SDK: 1.150

Supported Steam SDK Wrapper: 1.1.1

Supported SteamWorks: 1.31 1.32 1.33 1.34 1.35 1.36 1.37 1.38 1.39 1.40 1.41 1.42 1.43 1.44 1.45 1.46 1.47 1.48 1.49 1.50 1.51 1.52 1.53 1.54 1.55

To follow this steps you should register as a game developer at GOG and Steam first.
Also ask our support be to granted a license for the game (to enable online features).
 
1. Download an appropriate SteamWorks package from [https://partner.steamgames.com/](https://partner.steamgames.com/) and unpack it to **lib/steam/**
2. Download an appropriate Galaxy SDK package from [https://devportal.gog.com](https://devportal.gog.com/) and unpack it to **lib/galaxy/**
3. Download an appropriate Steam SDK Wrapper package from [https://devportal.gog.com](https://devportal.gog.com/) and unpack it to **lib/GalaxySteamWrapper/**
4. You might want to change CLIENT_ID and CLIENT_SECRET in GalaxyConfig.json to your own (you need to get it from GOG)
5. run cmake . -DCMAKE_BUILD_TYPE=Release/Debug (Visual Studio solution will be generated)
6. run cmake --build . --config Release/Debug
7. Make sure Galaxy Client is open
8. Run the demo game


### Documentation

Check out [Steam SDK Wrapper documentation](https://github.com/gogcom/gog-galaxy-dev-docs/blob/master/docs/steam-sdk-wrapper.md)

## PLEASE LEAVE YOUR FEEDBACK REGARDING YOUR EXPERIENCES WITH STEAM SDK WRAPPER THROUGH THIS [FORM](https://forms.gle/3h2oULcDGaDsZKMdA)

## ALSO IF YOU ENCOUNTER ANY PROBLEMS SUBMIT A TICKET USING DEVPORTAL'S SUPPORT SECTION
