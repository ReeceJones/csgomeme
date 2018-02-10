#include "Config.h"
#include "Settings.h"
#include "Enums.h"

/*
Configs:
We are going to want to allow the user to create the cfg name. This can
be achieved by just getting input from imgui::inputstr (not sure what string
input is for imgui lol). When starting game we can loop through all files
in config directory, then add to an array of available configs if they are valid.
There will also be a refresh button so that if you save a config mid game you can
refresh list and see what is there, we can call original function to get all configs.
We could possibly also call every 10th frame to be efficient. In order to make sure
that we are getting only configs that are for the cheat we will start each file with
[START] and end with [END]. When saving configs we will check if the config has been
created already. If it has we delete old one and write new values to config. If it hasnt,
we create new config file. Also want to change input text depending on if user has clicked config.

maybe something like :


________
Config1
Config2
Config3
New Config <- We don't fill in input box and we let user create name by renaming it
______

Day 2:
Fix config list in imgui, make it look nicer and make it so when you click on config it autofills.
Automatically get line indexes so that the configs have more flexibility between updates

*/


CConfig g_Config;

int SearchVector(std::vector<std::string> &InputVector, std::string String)
{
	for (int i = 0; i < InputVector.size(); i++)
	{
		int FixedIndex = InputVector[i].find_first_of(' {');
		FixedIndex -= 1;
		std::string NewStr = "";
		for (int z = 0; z < FixedIndex; z++)
		{
			NewStr += InputVector[i].at(z);
		}
		if (!NewStr.compare(String))
			return i;
	}

	return -1;
}

void CConfig::InitializeConfigSystem()
{
	//read stuff from default config
}

void CConfig::CreateConfig(char Path[MAX_PATH], char FileName[MAX_PATH])
{
	this->Buffer = ""; //clear buffer, dont want previous config's values to be carried over

	std::string TempStr = Path + std::string("\\") + FileName + std::string(".cfg");

	this->DeleteConfig((char*)TempStr.c_str());
	HANDLE file;
	CreateDirectoryA(Path, nullptr);
	file = CreateFileA(TempStr.c_str(), GENERIC_ALL, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
	CloseHandle(file);

	OFSTRUCT test;
	file = this->OpenConfig((char*)TempStr.c_str(), test, OF_READWRITE);


	/*	example of writing to config file	*/
	this->WriteBool("Aimbot-AntiUntrusted", Settings.Aimbot.AntiUntrust);
	this->WriteBool("Aimbot-Enabled", Settings.Aimbot.Enabled);
	this->WriteInt("Aimbot-AimbotMode", Settings.Aimbot.AimbotMode);
	this->WriteInt("Aimbot-Bone", Settings.Aimbot.Bone);
	this->WriteInt("Aimbot-EntityChecks", Settings.Aimbot.EntityChecks);
	this->WriteFloat("Aimbot-AutowallDamage", Settings.Aimbot.AutowallDamage);
	this->WriteBool("Aimbot-AutoShoot", Settings.Aimbot.AutoShoot);
	this->WriteBool("Aimbot-EnginePrediction", Settings.Aimbot.EnginePrediction);
	this->WriteInt("Aimbot-Key", Settings.Aimbot.Key);
	this->WriteFloat("Aimbot-Fov", Settings.Aimbot.Fov);
	this->WriteBool("Aimbot-SilentAim", Settings.Aimbot.SilentAim);
	this->WriteBool("Aimbot-NoRecoil", Settings.Aimbot.NoRecoil);
	this->WriteBool("Aimbot-AntiAim", Settings.Aimbot.AntiAim);
	this->WriteInt("Aimbot-AntiAim-Yaw", Settings.Aimbot.AntiAimYaw);
	this->WriteInt("Aimbot-AntiAim-Pitch", Settings.Aimbot.AntiAimPitch);
	this->WriteBool("Aimbot-AntiAim-LispY", Settings.Aimbot.LispY);
	this->WriteBool("Aimbot-AntiAim-LispX", Settings.Aimbot.LispX);
	this->WriteBool("Aimbot-AutoStop", Settings.Aimbot.AutoStop);
	this->WriteBool("Aimbot-AutoCrouch", Settings.Aimbot.AutoCrouch);
	this->WriteBool("Aimbot-Hitchance", Settings.Aimbot.Hitchance);
	this->WriteInt("Aimbot-Hitchance-Value", Settings.Aimbot.Hitchance);
	this->WriteFloat("Aimbot-SmoothY", Settings.Aimbot.SmoothY);
	this->WriteFloat("Aimbot-SmoothX", Settings.Aimbot.SmoothX);
	this->WriteBool("Aimbot-Resolver", Settings.Aimbot.Resolver);
	this->WriteBool("Aimbot-LagCompensation", Settings.Aimbot.LagCompensation);

	this->WriteBool("Misc-Bunnyhop", Settings.Misc.Bunnyhop);
	this->WriteBool("Misc-Namespam", Settings.Misc.NameSpam);
	this->WriteInt("Misc-AutoStrafe", Settings.Misc.AutoStrafe);
	this->WriteBool("Misc-NameStealer", Settings.Misc.NameStealer);
	this->WriteBool("Misc-Fakelag", Settings.Misc.FakeLag);
	this->WriteInt("Misc-Fakelag-Amount", Settings.Misc.FakeLagAmount);

	this->WriteBool("Visuals-Enabled", Settings.Visuals.Enabled);
	this->WriteBool("Visuals-Glow", Settings.Visuals.Glow);
	this->WriteFloat("Visuals-ViewModelFov", Settings.Visuals.ViewModelFov);
	this->WriteBool("Visuals-NoVisualRecoil", Settings.Visuals.NoVisRecoil);
	this->WriteFloat("Visuals-AimPunchFactor", Settings.Visuals.AimPunchFactor);
	this->WriteBool("Visuals-CustomPlayers", Settings.Visuals.CustomPlayers);
	this->WriteBool("Visuals-CustomGloves", Settings.Visuals.CustomGloves);
	this->WriteBool("Visuals-DrawPlayerBoxes", Settings.Visuals.DrawPlayerBoxes);
	this->WriteFloat("Visuals-BoxWidth", Settings.Visuals.BoxWidth);
	this->WriteBool("Visuals-DrawName", Settings.Visuals.DrawName);
	this->WriteBool("Visuals-DrawWeapon", Settings.Visuals.DrawWeapon);
	this->WriteInt("Visuals-DrawHealthBar", Settings.Visuals.DrawHealthBar);
	this->WriteInt("Visuals-DrawArmorBar", Settings.Visuals.DrawArmorBar);
	this->WriteFloat3("Visuals-GlowColorTerrorist", Settings.Visuals.GlowColorTerrorist);
	this->WriteFloat3("Visuals-GlowColorCounterTerrorist", Settings.Visuals.GlowColorCounterTerrorist);
	this->WriteFloat3("Visuals-BoxColorTerrorist", Settings.Visuals.BoxColorTerrorist);
	this->WriteFloat3("Visuals-BoxColorCounterTerrorist", Settings.Visuals.BoxColorCounterTerrorist);
	this->WriteFloat("Visuals-ThirdPerson", Settings.Visuals.ThirdPerson);
	this->WriteBool("Visuals-Chams", Settings.Visuals.Chams);
	this->WriteBool("Visuals-Chams-IgnoreZ", Settings.Visuals.IgnoreZ);
	this->WriteInt("Visuals-Chams-VisualStyle", Settings.Visuals.VisualStyle);
	this->WriteInt("Visuals-Chams-IgnoreZStyle", Settings.Visuals.IgnoreZStyle);
	this->WriteFloat3("Visuals-Chams-ChamsColorTerroristVisual", Settings.Visuals.ChamsColorTerroristVisual);
	this->WriteFloat3("Visuals-Chams-ChamsColorCounterTerroristVisual", Settings.Visuals.ChamsColorCounterTerroristVisual);
	this->WriteFloat3("Visuals-Chams-ChamsColorTerroristIgnoreZ", Settings.Visuals.ChamsColorTerroristIgnoreZ);
	this->WriteFloat3("Visuals-Chams-ChamsColorCounterTerroristIgnoreZ", Settings.Visuals.ChamsColorCounterTerroristIgnoreZ);

	/*										*/
	this->WriteBufferToFile(Path, FileName);
	/*										*/		

	CloseHandle(file);
}

HANDLE CConfig::OpenConfig(char Name[MAX_PATH], OFSTRUCT &ofstruct, UINT Action)
{
	return (HANDLE)OpenFile(Name, &ofstruct, Action);
}

void CConfig::WriteCharToConfig(HANDLE file, const char *StringToWrite)
{
	DWORD BytesToWrite = (DWORD)strlen(StringToWrite);
	DWORD BytesWritten = 0;
	WriteFile(file, StringToWrite, BytesToWrite, &BytesWritten, NULL);
	CloseHandle(file);
}

void CConfig::DeleteConfig(char Path[MAX_PATH])
{
	DeleteFileA(Path);
}

std::vector<std::string> CConfig::ReadConfig(char Path[MAX_PATH])
{
	std::vector<std::string> contents;
	std::ifstream hFile(Path);

	std::string line;
	while (std::getline(hFile, line))
	{
		contents.push_back(line);
	}

	return contents;
}

void CConfig::WriteBufferToFile(char Path[MAX_PATH], char FileName[MAX_PATH])
{	

	std::string TempStr = Path + std::string("\\") + FileName + std::string(".cfg");

	OFSTRUCT ofstruct;
	HANDLE file = this->OpenConfig((char*)TempStr.c_str(), ofstruct, OF_READWRITE);



	while ((HFILE)file == HFILE_ERROR)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)	//not best way of checking if a file exists, but gets job done
		{
			this->CreateConfig(Path, FileName); //attempt to create new file
			file = this->OpenConfig((char*)TempStr.c_str(), ofstruct, OF_READWRITE);
		}
		else if (GetLastError() == ERROR_ACCESS_DENIED)
		{
			this->DeleteConfig(Path);
			this->CreateConfig(Path, FileName); //attempt to create new file
			file = this->OpenConfig((char*)TempStr.c_str(), ofstruct, OF_READWRITE);
		}
		else if ((HFILE)file == HFILE_ERROR)
			return; //abort
	}

	this->WriteCharToConfig(file, this->Buffer.c_str()); //write our buffer to the config file
}

std::vector<std::string> CConfig::GetAllConfigs(std::string Path)
{
	HANDLE dir;
	WIN32_FIND_DATA file_data;
	std::vector<std::string> Files;
	Files.clear();

	if ((dir = FindFirstFile((Path + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return Files; /* No files found */

	do 
	{
		const string file_name = file_data.cFileName;
		const string full_file_name = file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		Files.push_back(full_file_name);
	} 
	while (FindNextFile(dir, &file_data));
	FindClose(dir);

	std::vector<std::string> Result;
	Result.clear();
	for (int i = 0; i < Files.size(); i++)
		if (strstr(Files[i].c_str(), ".cfg"))
			Result.push_back(Files[i]);

	return Result;
}

void CConfig::LoadConfig(char Path[MAX_PATH])
{
	std::string StringToRead = std::string("C:\\GooseHook\\") + Path + std::string(".cfg");

	OFSTRUCT ofstruct;
	if ((HFILE)this->OpenConfig((char*)StringToRead.c_str(), ofstruct, OF_READWRITE) == HFILE_ERROR)
		return;
	std::vector<std::string> Lines = this->ReadConfig((char*)StringToRead.c_str());
	std::string StringToBeParsed = "";

	Settings.Aimbot.AntiUntrust = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AntiUntrusted")]);
	Settings.Aimbot.Enabled = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-Enabled")]);
	Settings.Aimbot.AimbotMode = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AimbotMode")]);
	Settings.Aimbot.Bone = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-Bone")]);
	Settings.Aimbot.EntityChecks = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-EntityChecks")]);
	Settings.Aimbot.AutowallDamage = this->ParseFloat(Lines[SearchVector(Lines, "Aimbot-AutowallDamage")]);
	Settings.Aimbot.AutoShoot = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AutoShoot")]);
	Settings.Aimbot.EnginePrediction = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-EnginePrediction")]);
	Settings.Aimbot.Key = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-Key")]);
	Settings.Aimbot.Fov = this->ParseFloat(Lines[SearchVector(Lines, "Aimbot-Fov")]);
	Settings.Aimbot.SilentAim = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-SilentAim")]);
	Settings.Aimbot.NoRecoil = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-NoRecoil")]);
	Settings.Aimbot.AntiAim = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AntiAim")]);
	Settings.Aimbot.AntiAimYaw = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-AntiAim-Yaw")]);
	Settings.Aimbot.AntiAimPitch = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-AntiAim-Pitch")]);
	Settings.Aimbot.LispY = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AntiAim-LispY")]);
	Settings.Aimbot.LispX = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AntiAim-LispX")]);
	Settings.Aimbot.AutoStop = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AutoStop")]);
	Settings.Aimbot.AutoCrouch = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-AutoCrouch")]);
	Settings.Aimbot.HitchanceEnabled = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-Hitchance")]);
	Settings.Aimbot.Hitchance = this->ParseInt(Lines[SearchVector(Lines, "Aimbot-Hitchance-Value")]);
	Settings.Aimbot.SmoothY = this->ParseFloat(Lines[SearchVector(Lines, "Aimbot-SmoothY")]);
	Settings.Aimbot.SmoothX = this->ParseFloat(Lines[SearchVector(Lines, "Aimbot-SmoothX")]);
	Settings.Aimbot.Resolver = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-Resolver")]);
	Settings.Aimbot.LagCompensation = this->ParseBool(Lines[SearchVector(Lines, "Aimbot-LagCompensation")]);

	Settings.Misc.Bunnyhop = this->ParseBool(Lines[SearchVector(Lines, "Misc-Bunnyhop")]);
	Settings.Misc.NameSpam = this->ParseBool(Lines[SearchVector(Lines, "Misc-Namespam")]);
	Settings.Misc.AutoStrafe = this->ParseInt(Lines[SearchVector(Lines, "Misc-AutoStrafe")]);
	Settings.Misc.NameStealer = this->ParseBool(Lines[SearchVector(Lines, "Misc-NameStealer")]);
	Settings.Misc.FakeLag = this->ParseBool(Lines[SearchVector(Lines, "Misc-Fakelag")]);
	Settings.Misc.FakeLagAmount = this->ParseInt(Lines[SearchVector(Lines, "Misc-Fakelag-Amount")]);


	Settings.Visuals.Enabled = this->ParseBool(Lines[SearchVector(Lines, "Visuals-Enabled")]);
	Settings.Visuals.Glow = this->ParseBool(Lines[SearchVector(Lines, "Visuals-Glow")]);
	Settings.Visuals.ViewModelFov = this->ParseFloat(Lines[SearchVector(Lines, "Visuals-ViewModelFov")]);
	Settings.Visuals.NoVisRecoil = this->ParseBool(Lines[SearchVector(Lines, "Visuals-NoVisualRecoil")]);
	Settings.Visuals.AimPunchFactor = this->ParseFloat(Lines[SearchVector(Lines, "Visuals-AimPunchFactor")]);
	Settings.Visuals.CustomPlayers = this->ParseBool(Lines[SearchVector(Lines, "Visuals-CustomPlayers")]);
	Settings.Visuals.CustomGloves = this->ParseBool(Lines[SearchVector(Lines, "Visuals-CustomGloves")]);
	Settings.Visuals.DrawPlayerBoxes = this->ParseBool(Lines[SearchVector(Lines, "Visuals-DrawPlayerBoxes")]);
	Settings.Visuals.BoxWidth = this->ParseFloat(Lines[SearchVector(Lines, "Visuals-BoxWidth")]);
	Settings.Visuals.DrawName = this->ParseBool(Lines[SearchVector(Lines, "Visuals-DrawName")]);
	Settings.Visuals.DrawWeapon = this->ParseBool(Lines[SearchVector(Lines, "Visuals-DrawWeapon")]);
	Settings.Visuals.DrawHealthBar = this->ParseInt(Lines[SearchVector(Lines, "Visuals-DrawHealthBar")]);
	Settings.Visuals.DrawArmorBar = this->ParseInt(Lines[SearchVector(Lines, "Visuals-DrawArmorBar")]);

	ConfigVector GlowColorTerrorist = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-GlowColorTerrorist")]);
	Settings.Visuals.GlowColorTerrorist[0] = GlowColorTerrorist.f1;
	Settings.Visuals.GlowColorTerrorist[1] = GlowColorTerrorist.f2;
	Settings.Visuals.GlowColorTerrorist[2] = GlowColorTerrorist.f3;
	
	ConfigVector GlowColorCounterTerrorist = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-GlowColorCounterTerrorist")]);
	Settings.Visuals.GlowColorCounterTerrorist[0] = GlowColorCounterTerrorist.f1;
	Settings.Visuals.GlowColorCounterTerrorist[1] = GlowColorCounterTerrorist.f2;
	Settings.Visuals.GlowColorCounterTerrorist[2] = GlowColorCounterTerrorist.f3;

	ConfigVector BoxColorTerrorist = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-BoxColorTerrorist")]);
	Settings.Visuals.BoxColorTerrorist[0] = BoxColorTerrorist.f1;
	Settings.Visuals.BoxColorTerrorist[1] = BoxColorTerrorist.f2;
	Settings.Visuals.BoxColorTerrorist[2] = BoxColorTerrorist.f3;

	ConfigVector BoxColorCounterTerrorist = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-BoxColorCounterTerrorist")]);
	Settings.Visuals.BoxColorCounterTerrorist[0] = BoxColorCounterTerrorist.f1;
	Settings.Visuals.BoxColorCounterTerrorist[1] = BoxColorCounterTerrorist.f2;
	Settings.Visuals.BoxColorCounterTerrorist[2] = BoxColorCounterTerrorist.f3;
	
	Settings.Visuals.ThirdPerson = this->ParseFloat(Lines[SearchVector(Lines, "Visuals-ThirdPerson")]);
	Settings.Visuals.Chams = this->ParseBool(Lines[SearchVector(Lines, "Visuals-Chams")]);
	Settings.Visuals.IgnoreZ = this->ParseBool(Lines[SearchVector(Lines, "Visuals-Chams-IgnoreZ")]);
	Settings.Visuals.VisualStyle = this->ParseInt(Lines[SearchVector(Lines, "Visuals-Chams-VisualStyle")]);
	Settings.Visuals.IgnoreZStyle = this->ParseInt(Lines[SearchVector(Lines, "Visuals-Chams-IgnoreZStyle")]);
	
	ConfigVector ChamsColorTerroristVisual = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-Chams-ChamsColorTerroristVisual")]);
	Settings.Visuals.ChamsColorTerroristVisual[0] = ChamsColorTerroristVisual.f1;
	Settings.Visuals.ChamsColorTerroristVisual[1] = ChamsColorTerroristVisual.f2;
	Settings.Visuals.ChamsColorTerroristVisual[2] = ChamsColorTerroristVisual.f3;

	ConfigVector ChamsColorCounterTerroristVisual = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-Chams-ChamsColorCounterTerroristVisual")]);
	Settings.Visuals.ChamsColorCounterTerroristVisual[0] = ChamsColorCounterTerroristVisual.f1;
	Settings.Visuals.ChamsColorCounterTerroristVisual[1] = ChamsColorCounterTerroristVisual.f2;
	Settings.Visuals.ChamsColorCounterTerroristVisual[2] = ChamsColorCounterTerroristVisual.f3;

	ConfigVector ChamsColorTerroristIgnoreZ = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-Chams-ChamsColorTerroristIgnoreZ")]);
	Settings.Visuals.ChamsColorTerroristIgnoreZ[0] = ChamsColorTerroristIgnoreZ.f1;
	Settings.Visuals.ChamsColorTerroristIgnoreZ[1] = ChamsColorTerroristIgnoreZ.f2;
	Settings.Visuals.ChamsColorTerroristIgnoreZ[2] = ChamsColorTerroristIgnoreZ.f3;

	ConfigVector ChamsColorCounterTerroristIgnoreZ = this->ParseFloat3(Lines[SearchVector(Lines, "Visuals-Chams-ChamsColorCounterTerroristIgnoreZ")]);
	Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[0] = ChamsColorCounterTerroristIgnoreZ.f1;
	Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[1] = ChamsColorCounterTerroristIgnoreZ.f2;
	Settings.Visuals.ChamsColorCounterTerroristIgnoreZ[2] = ChamsColorCounterTerroristIgnoreZ.f3;
}

int CConfig::ParseInt(std::string StringToParse)
{
	int FirstIndex = StringToParse.find("{");
	int SecondIndex = StringToParse.find("}");
	std::string MiddleString = "";
	for (int i = FirstIndex + 1; i < SecondIndex; i++)
	{
		MiddleString += StringToParse[i];
	}
	return atoi(MiddleString.c_str());
}

bool CConfig::ParseBool(std::string StringToParse)
{
	int FirstIndex = StringToParse.find("{");
	int SecondIndex = StringToParse.find("}");
	std::string MiddleString = "";
	for (int i = FirstIndex + 1; i < SecondIndex; i++)
	{
		MiddleString += StringToParse[i];
	}
	int Val = atoi(MiddleString.c_str());
	if (Val > 1)
		Val = 1;
	else if (Val < 0)
		Val = 0;
	return (bool)Val;
}

float CConfig::ParseFloat(std::string StringToParse)
{
	int FirstIndex = StringToParse.find("{");
	int SecondIndex = StringToParse.find("}");
	std::string MiddleString = "";
	for (int i = FirstIndex + 1; i < SecondIndex; i++)
	{
		MiddleString += StringToParse[i];
	}
	return atof(MiddleString.c_str());
}

std::string CConfig::ParseString(std::string StringToParse)
{
	int FirstIndex = StringToParse.find("{");
	int SecondIndex = StringToParse.find("}");
	std::string MiddleString = "";
	for (int i = FirstIndex + 1; i < SecondIndex; i++)
	{
		MiddleString += StringToParse[i];
	}
	return MiddleString;
}

ConfigVector CConfig::ParseFloat3(std::string StringToParse)
{
	static int Accuracy = 2; /*this is the amount of numbers that will follow decimal. Have this so we can speed up parsing a little bit. 
							 You can set to insane value if you dont want to use*/
	int FirstIndex = StringToParse.find("{");
	int SecondIndex = StringToParse.find("}");
	std::vector<std::string> MiddleString;
	MiddleString.clear();
	std::vector<int> Commas;
	for (int i = FirstIndex + 1; i < SecondIndex; i++)
	{
		if (StringToParse[i] == ',')
			Commas.push_back(i);
	}
	std::vector<std::string> ParsedVector;
	ParsedVector.clear();
	for (int i = 0; i < 3; i++) //loop 3 times because ConfigVector contains only 3 values
	{
		int BeginningIndex;
		int EndIndex;
		if (i == 0)
		{
			BeginningIndex = FirstIndex + 1;
			EndIndex = Commas[0];
		}
		else if (i == 1)
		{
			BeginningIndex = Commas[0] + 1;
			EndIndex = Commas[1];
		}
		else if (i == 2)
		{
			BeginningIndex = Commas[1] + 1;
			EndIndex = SecondIndex;
		}

		int AfterDecimalcount = 0;
		bool Notice = false;
		std::string TempString = "";
		for (int z = BeginningIndex; z < EndIndex; z++)
		{

			TempString += StringToParse[z];

			if (StringToParse[z] == '.')
				Notice = true;
			if (Notice)
				AfterDecimalcount += 1;
			if (AfterDecimalcount == Accuracy + 1)
				z = EndIndex;
		}
		ParsedVector.push_back(TempString);
	}

	float fArray[3] = {
		atof(ParsedVector[0].c_str()),
		atof(ParsedVector[1].c_str()),
		atof(ParsedVector[2].c_str())
	};
	ConfigVector ReturnVector(fArray[0], fArray[1], fArray[2]);

	return ReturnVector;
}

void CConfig::WriteInt(std::string Name, int Value)
{
	std::string WriteStr = Name + " {" + std::to_string(Value) + "}\n";
	this->Buffer += WriteStr;
}

void CConfig::WriteBool(std::string Name, bool Value)
{
	std::string WriteStr = Name + " {" + std::to_string(Value) + "}\n";
	this->Buffer += WriteStr;
}

void CConfig::WriteFloat(std::string Name, float Value)
{
	std::string WriteStr = Name + " {" + std::to_string(Value) + "}\n";
	this->Buffer += WriteStr;
}

void CConfig::WriteString(std::string Name, std::string Value)
{
	std::string WriteStr = Name + " {" + Value + "}\n";
	this->Buffer += WriteStr;
}

void CConfig::WriteFloat3(std::string Name, float Value[3])
{
	std::string WriteStr = Name + " {" + std::to_string(Value[0]) + ',' + std::to_string(Value[1]) + ',' + std::to_string(Value[2]) + "}\n";
	this->Buffer += WriteStr;
}
