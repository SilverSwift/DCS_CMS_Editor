function Component()
{
	if (installer.isUninstaller()) {
		installer.setDefaultPageVisible(QInstaller.Introduction, false);
		gui.clickButton(buttons.NextButton); // automatically click the Next button
	}
}


Component.prototype.createOperations = function()
{
    component.createOperations();
	
	if (systemInfo.productType === "windows") {
        component.addOperation(
							"CreateShortcut", 
							"@TargetDir@/YOPT.exe", 
							"@StartMenuDir@/YOPT.lnk",
							"workingDirectory=@TargetDir@", 
							"iconPath=@TargetDir@/YOPT.exe", "iconId=0", 
							"description=Run your own presets tweaker");
							
		component.addOperation(
							"CreateShortcut", 
							"@TargetDir@/maintenancetool.exe", 
							"@StartMenuDir@/Uninstall_YOPT.lnk",
							"workingDirectory=@TargetDir@", 
							"iconPath=@TargetDir@/maintenancetool.exe", "iconId=0", 
							"description=Remove your own presets tweaker from the PC");
			
		component.addOperation(
							"CreateShortcut", 
                            "@TargetDir@/YOPT.exe",
                            "@DesktopDir@/YOPT.lnk",
                            "workingDirectory=@TargetDir@",
                            "iconPath=@TargetDir@/YOPT.exe", "iconId=0",
                            "description=Run your own presets tweaker");
    }
}
