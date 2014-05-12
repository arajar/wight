-------------------------------------------------------------------------------
-- 
-------------------------------------------------------------------------------

include "../tools/premake/common/"

-------------------------------------------------------------------------------

solution "wight"

	math.randomseed(string.hash(solution().name))
  	startproject "wight"
	addCommonConfig()

-------------------------------------------------------------------------------

project "wight"

	files 
	{
		 "../src/**",
		 "../include/**",
	}

	includedirs 
	{ 
		"../include/", 
		"../libs/glm/glm/",
		"../libs/SFML-2.1/include",
	}

	libdirs 
	{ 
		"../libs/SFML-2.1/lib/" .. _OPTIONS["arch"],
	}

	kind "ConsoleApp"

	uuid "BDF8292E-B782-41BC-966F-8F8DEF9F9D87"

	targetdir("../release/" )
	postbuildcommands
	{
		"echo Copying dlls...",
		"robocopy $(SolutionDir)../../../libs/SFML-2.1/bin/" .. _OPTIONS["arch"] .. "/ $(targetDir) > log.txt",
		"exit 0",
	}

	configuration "Debug"
		flags( "NoExceptions" )
		targetname( "wight" .. _OPTIONS["arch"] .. "_d" )

		links 
		{
			"sfml-graphics-d.lib",
			"sfml-window-d.lib",
			"sfml-system-d.lib",
		}

	configuration "Release"
		flags( "NoExceptions" )
		targetname( "wight" .. _OPTIONS["arch"])
		links 
		{
			"sfml-graphics.lib",
			"sfml-window.lib",
			"sfml-system.lib",
		}

---------------------------------------------------------------------------

