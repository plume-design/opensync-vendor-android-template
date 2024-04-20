OpenSync Android Template
=========================

An example/template vendor layer implementation for Android-based devices.

Target:
* `ANDROID_GENERIC` - generic Android implementation

The example implementation can be used to create a custom vendor layer for
the specific hardware at hand.

#### Reference software versions

* Components and versions:

    | Component                        | Version     |         |
    |----------------------------------|-------------|---------|
    | OpenSync core                    | 6.2.x       | public  |
    | OpenSync vendor/android-template | 6.2.x       | public  |
    | OpenSync platform/android        | 6.2.x       | public  |
    | Android                          | >= 9.0      | public  |

#### Hardware information

* Interfaces:

    | Interface     | Description                                       |
    |---------------|---------------------------------------------------|
    | eth0          | ethernet interface                                |
    | wlan0         | Wi-Fi STA interface                               |


OpenSync root directory
-----------------------

OpenSync build system requires a certain directory structure in order to ensure
modularity. Key components are:

* OpenSync core:                  `${OPENSYNC_ROOT}/core`
* OpenSync Android platform:      `${OPENSYNC_ROOT}/platform/android`
* OpenSync vendor layer template: `${OPENSYNC_ROOT}/vendor/android-template`
* OpenSync service provider:      `${OPENSYNC_ROOT}/service-provider/local` ([local](https://github.com/plume-design/opensync-service-provider-local) given as an example which needs to be replaced with your service provider)

Follow these steps to populate the ${OPENSYNC_ROOT} directory:

```
$ git clone --branch osync_6.2.x https://github.com/plume-design/opensync.git ${OPENSYNC_ROOT}/core
$ git clone --branch osync_6.2.x https://github.com/plume-design/opensync-platform-android.git ${OPENSYNC_ROOT}/platform/android
$ git clone --branch osync_6.2.x https://github.com/plume-design/opensync-vendor-android-template.git ${OPENSYNC_ROOT}/vendor/android-template
$ git clone --branch osync_6.2.x https://github.com/plume-design/opensync-service-provider-local.git ${OPENSYNC_ROOT}/service-provider/local
$ mkdir -p ${OPENSYNC_ROOT}/3rdparty
```

The resulting layout should be as follows:

```
${OPENSYNC_ROOT}
├── 3rdparty
│   └── ...
├── core
│   ├── 3rdparty -> ../3rdparty
│   ├── build
│   ├── doc
│   ├── docker
│   ├── interfaces
│   ├── kconfig
│   ├── Makefile
│   ├── ovsdb
│   ├── platform -> ../platform
│   ├── README.md
│   ├── rootfs
│   ├── service-provider -> ../service-provider
│   ├── src
│   └── vendor -> ../vendor
├── platform
│   └── android
├── service-provider
│   └── local
└── vendor
    └── android-template
```


Build
-----

1. Clone the build system provided in **opensync-sdk-android** repository:
```
git clone --branch osync_6.2.x https://github.com/plume-design/opensync-sdk-android.git ${SDK_ROOT}
```

2. In `${SDK_ROOT}`, run `make` with `OPENSYNC_SRC` specified:
```
make OPENSYNC_SRC=${OPENSYNC_ROOT} build
```

The resulting APK package is located in `build-android-generic/apk/app/build/outputs/apk`.


Install and run
---------------

Install and run the OpenSync APK on your Android device using the standard method.


### Android 10 W^X Violation

Up to Android 9 (`targetSdkVersion` <= 28), apps were able to invoke `exec()` on binary code embedded within app's APK file.  
On Android 10 (`targetSdkVersion` > 28) however, W^X restrictions do not allow app's data files to be executed, even if signed with the platform key (system app).

Example of logged errors:
```
10-21 00:13:33.608  4892  4892 W Thread-3: type=1400 audit(0.0:460): avc: denied { execute } for name="ovsdb-server" dev="mmcblk0p23" ino=459791 scontext=u:r:system_app:s0 tcontext=u:object_r:system_app_data_file:s0 tclass=file permissive=0
10-21 00:13:33.616  4851  4889 W System.err: java.io.IOException: Cannot run program "/data/user/0/com.opensync.app/files/bin/ovsdb-server": error=13, Permission denied
10-21 00:13:33.617  4851  4889 W System.err: 	at com.opensync.app.OpenSyncBootStrap$1.run(OpenSyncBootStrap.java:189)
10-21 00:13:33.612  4893  4893 W Thread-2: type=1400 audit(0.0:461): avc: denied { execute } for name="dm" dev="mmcblk0p23" ino=459829 scontext=u:r:system_app:s0 tcontext=u:object_r:system_app_data_file:s0 tclass=file permissive=0
10-21 00:13:33.622  4851  4888 W System.err: java.io.IOException: Cannot run program "/data/user/0/com.opensync.app/files/opensync/bin/dm": error=13, Permission denied
10-21 00:13:33.622  4851  4888 W System.err: 	at com.opensync.app.OpenSyncBootStrap$1.run(OpenSyncBootStrap.java:189)
```

To fix the issue, a separate set of Android SELinux rules is needed for the OpenSync app. These rules must be based on the same foundation as the System App, with some additional rules incorporated.
Refer to the directory of `${SDK_ROOT}/sepolicy` and apply the patches to your Android [sepolicy](https://android.googlesource.com/platform/system/sepolicy/) source code. Note that sepolicy may vary for different Android versions. The patches include changes for API levels 28 to 33. You should refer to these modifications and subsequently port them to your sepolicy directory based on your Android version.

For more information, see https://issuetracker.google.com/issues/128554619.


Device access
-------------

To access the device (e.g. for debugging) use '[Android Debug Bridge (adb)](https://developer.android.com/tools/adb)'.


OpenSync resources
------------------

For further information please visit: https://www.opensync.io/
