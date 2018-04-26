# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.a4-dance.Debug:
/Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/Debug/a4-dance:\
	/Users/administrator/Desktop/repo-qinxx215/lib/MinGfx-1.0/libMinGfx.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/administrator/Desktop/repo-qinxx215/lib/libnanogui.dylib
	/bin/rm -f /Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/Debug/a4-dance


PostBuild.a4-dance.Release:
/Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/Release/a4-dance:\
	/Users/administrator/Desktop/repo-qinxx215/lib/MinGfx-1.0/libMinGfx.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/administrator/Desktop/repo-qinxx215/lib/libnanogui.dylib
	/bin/rm -f /Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/Release/a4-dance


PostBuild.a4-dance.MinSizeRel:
/Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/MinSizeRel/a4-dance:\
	/Users/administrator/Desktop/repo-qinxx215/lib/MinGfx-1.0/libMinGfx.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/administrator/Desktop/repo-qinxx215/lib/libnanogui.dylib
	/bin/rm -f /Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/MinSizeRel/a4-dance


PostBuild.a4-dance.RelWithDebInfo:
/Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/RelWithDebInfo/a4-dance:\
	/Users/administrator/Desktop/repo-qinxx215/lib/MinGfx-1.0/libMinGfx.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Users/administrator/Desktop/repo-qinxx215/lib/libnanogui.dylib
	/bin/rm -f /Users/administrator/Desktop/repo-qinxx215/dev/a4-dance/build/RelWithDebInfo/a4-dance




# For each target create a dummy ruleso the target does not have to exist
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd:
/Users/administrator/Desktop/repo-qinxx215/lib/MinGfx-1.0/libMinGfx.a:
/Users/administrator/Desktop/repo-qinxx215/lib/libnanogui.dylib:
