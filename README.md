# Virtual Display Driver
Based on Microsoft Indirect Display Driver Sample. This creates a virtual display in Windows that acts and functions just like a real one. It's useful for streaming, virtual reality applications, recording, headless servers, etc. The benefit over a physical display is the ability to adjust resolutions and refresh rates beyond the physical displays capabilities. For example, this would enable the ability to stream a game from your home PC using game streaming software at 240hz at 8K while owning a 60hz 1080p monitor (unrealistic, but explains the abilities well). For servers without displays, this enabled remote desktop and screen streaming to other systems as if there were a display installed. 

Supports emulating resolutions from **640 x 480** to **7680 x 4320 (8K)**, and refresh rates including **60hz, 75hz, 90hz, 120hz, 144hz, 165hz, 240hz, 480hz,** and **500hz.**

This project uses the official Windows Indirect Display Driver combined with the IddCx class extension driver.

## Download Stable Version

> [!IMPORTANT]
> Please make sure you download the correct version for your operating system!

- [Windows 10 and 11 (no HDR)](https://github.com/itsmikethetech/Virtual-Display-Driver/releases/tag/23.10.20.2)
- [Windows 11 23H2+ (HDR)](https://github.com/itsmikethetech/Virtual-Display-Driver/releases/tag/23.12.2HDR)

## Download Beta
- [Universal Driver - 24.10.27 (Windows 10/11)](https://github.com/itsmikethetech/Virtual-Display-Driver/releases/tag/24.10.27) - Added more plus optimisations

[Edid database by bud (beta only - for custom edid) ](https://edid.mikethetech.com/)

 
## Installation

### Release Instructions

1. Download the latest version from the above or the website, and extract the contents to a folder.
2. Copy the `\IddSampleDriver\` folder and its contents to `C:\IddSampleDriver\` before installing the driver **(important!)**.
3. Right click and run the *.bat file **as an Administrator** to add the driver certificate as a trusted root certificate.
4. Don't install the inf. Open device manager, click on any device, then click on the "Action" menu and click "Add Legacy Hardware".
5. Select "Add hardware from a list (Advanced)" and then select Display adapters.
6. Click "Have Disk..." and click the "Browse..." button. Navigate to the extracted files and select the inf file.
7. You are done! Go to display settings to customize the resolution of the additional displays. These displays show up in Sunshine, your Oculus or VR settings, and should be able to be streamed from.
8. You can enable/disable the display adapter to toggle the monitors.

**Ps.** Make sure that `options.txt` is accessible for the system at `C:\IddSampleDriver\options.txt` or the installation will fail.

---

### Beta Release Instructions

1. Download the beta version and extract the contents to a folder.
2. Copy the `\VirtualDisplayDriver\` folder and its contents to `C:\VirtualDisplayDriver\` before installing the driver **(important!)**.
3. Right click and run the *.bat file **as an Administrator** to add the driver certificate as a trusted root certificate.
4. Don't install the inf. Open device manager, click on any device, then click on the "Action" menu and click "Add Legacy Hardware".
5. Select "Add hardware from a list (Advanced)" and then select Display adapters.
6. Click "Have Disk..." and click the "Browse..." button. Navigate to the extracted files and select the inf file.
7. You are done! Go to display settings to customize the resolution of the additional displays. These displays show up in Sunshine, your Oculus or VR settings, and should be able to be streamed from.
8. You can enable/disable the display adapter to toggle the monitors.


## Easy Uninstall

1. Open device manager
2. Locate Display Adapters
3. Right click on IddSampleDriver, choose "Uninstall device"
4. There is a new popup window, in there click Attempt to remove driver for this device.


## Manual/Forced Uninstall

Next instructions are for those cases where the device is removed from the system, but driver stil remains. This happens when there is a connection to the device while trying to remove the drivers. To
remedy this, there is a a few tricks built into windows. So here goes:

1. Open up a powershell terminal and input this:
2.  ```pnputil /enum-drivers```
3. Locate iddsampledriver.inf, there might be multiple pages of text. Make a note of the "published name", it's often unique for your system, but might look like "oem139.inf"
4.  ```pnputil /delete-driver oem139.inf```
5.  (If you still get multiple displays after uninstall, try to repeat uninstall procedure in safemode.)

### Removing Certificates (Optional)

To uninstall the root certificate:

1. Search for "Manage computer certificates" from the Start menu and open the app.
2. In the sidebar, expand `Trusted Root Certification Authorities` -> `Certificates` folder.
3. Scroll to the bottom, until you see "Virtual Display Driver".
4. Right click "Virtual Display Driver" and hit "Delete". In the warning that appears, choose "Yes".
5. In the sidebar, expand `Trusted Publishers` -> `Certificates` folder.
6. Scroll to the bottom, until you see "Virtual Display Driver". 
7. Right click "Virtual Display Driver" and hit "Delete". In the warning that appears, choose "Yes".


## HDR Support Now Available for Windows 11 22H2+ 

### Videos

[![thumbnail2023](https://github.com/itsmikethetech/Virtual-Display-Driver/assets/25166211/1a64c390-5d8a-420f-8bb9-4642349fc132)](https://youtu.be/nNWpbRUPkn4 "How to install a virtual display")

[Previous Video: How to install a virtual display](https://youtu.be/byfBWDnToYk "How to install a virtual display")

### Screenshots:

![image](https://github.com/itsmikethetech/Virtual-Display-Driver/assets/25166211/0f1dfed6-c9ac-4cb6-92cf-7d9ab2ac0c66)

![image](https://github.com/itsmikethetech/Virtual-Display-Driver/assets/25166211/5cb8ce08-890f-4bc1-a1a6-34f22e103699)

![image](https://github.com/itsmikethetech/Virtual-Display-Driver/assets/25166211/02af86f2-b896-4265-9174-b17c9a1aeab7)

## License

MIT and CC0 or Public Domain (for changes I made, please consult Microsoft for their license), choose the least restrictive option.

## Disclaimer:

This software is provided "AS IS" with NO IMPLICIT OR EXPLICIT warranty. It's worth noting that while this software functioned without issues on my system, there is no guarantee that it will not impact your computer. It operates in User Mode, which reduces the likelihood of causing system instability, such as the Blue Screen of Death. However, exercise caution when using this software.

## Acknowledgements

Shoutout to **[MikeTheTech](https://github.com/itsmikethetech)** Project Boss man, owner and programmer!

Shoutout to **[Bud](https://github.com/bud3699)** and **[zjoasan](https://github.com/zjoasan)** for jumping on the team and helping with not just support, but lots of great new features!

Shoutout to **[Roshkins](https://github.com/roshkins/IddSampleDriver)** for the original repo.

Shoutout to **[Baloukj](https://github.com/baloukj/IddSampleDriver)** for the 8-bit / 10-bit support. (Also, first to push the new Microsoft Driver public!)

Shoutout to **[Anakngtokwa](https://github.com/Anakngtokwa)** for assisting with finding driver sources.

**[Microsoft](https://github.com/microsoft/Windows-driver-samples/tree/master/video/IndirectDisplay)** Indirect Display Driver/Sample (Driver code)

Thanks to **[AKATrevorJay](https://github.com/akatrevorjay/edid-generator)** for the hi-res EDID.

Shoutout to **[LexTrack](https://github.com/lextrack/)** for the MiniScreenRecorder script. 

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=VirtualDisplay/Virtual-Display-Driver&type=Date)](https://star-history.com/#VirtualDisplay/Virtual-Display-Driver&Date)

