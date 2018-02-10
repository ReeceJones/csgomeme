#include "Hooks.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_dx9.h"
#include "Settings.h"
#include "Convar.h"
#include "Interfaces.h"
#include "Config.h"
#include "Gui.h"

#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);
EndSceneFn EndScene_Original;
tReset ResetScene_Original;
WNDPROC WndProc_Original;
HWND Window;
bool CurKey[256] = {};
void GUI_Init(IDirect3DDevice9* pDevice);
static LPDIRECT3DTEXTURE9       g_FontTexture = NULL;
static bool Initialized = false;
CSettings Settings;
ConVar* CVar = new ConVar;
static bool AimTab = true;
static bool VisualsTab = false;
static bool MiscTab = false;

const char* Keys[] =
{
	"No HotKey",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};

LRESULT __stdcall Hooks::WndProc_Hooked(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		CurKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		CurKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		CurKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		CurKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		CurKey[wParam] = true;
		break;
	case WM_KEYUP:
		CurKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{
		static auto isDown = false;
		static auto isClicked = false;
		if (CurKey[VK_INSERT])
		{
			isClicked = false;
			isDown = true;
		}
		else if (!CurKey[VK_INSERT] && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}
		if (isClicked)
		{
			Settings.Menu.MenuOpened = !Settings.Menu.MenuOpened;

			static auto cl_mouseenable = Interfaces::Cvar->FindVar("cl_mouseenable");

			cl_mouseenable->SetValue(!Settings.Menu.MenuOpened);
		}

	}
	if (Initialized && Settings.Menu.MenuOpened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return CallWindowProc(WndProc_Original, hWnd, uMsg, wParam, lParam);
}


HRESULT __stdcall Hooks::EndScene_Hooked(IDirect3DDevice9* pDevice)
{
	if (!Initialized)
	{
		GUI_Init(pDevice);
	}
	else
	{
		//GuiVector2 xd;
		//xd.y = 500;																										//this bugs imgui out. comment out
		//xd.x = 500;

		//g_pDraw->DrawCircleGradient(xd, 25, true, D3DCOLOR_XRGB(200, 200, 200), D3DCOLOR_XRGB(150, 150, 150), 0.2f, pDevice);

			//g_pDraw->DrawCircle(xd , 50, false, D3DCOLOR_XRGB(255, 0, 0), pDevice);

			//GuiVector4 lmao;

			//lmao.x1 = 250;
			//lmao.y1 = 300;
			//lmao.x2 = 750;
			//lmao.y2 = 500;

			//g_pDraw->DrawLine(lmao, D3DCOLOR_XRGB(0, 255, 0), pDevice);


			//GuiVector6 ecks;
			//ecks.x1 = 100;
			//ecks.x2 = 200;
			//ecks.x3 = 150;
			//ecks.y1 = 200;
			//ecks.y2 = 200;
			//ecks.y3 = 300;


			//g_pDraw->DrawTriangle(ecks, false, D3DCOLOR_XRGB(0, 0, 255), pDevice);

			//GuiVector4 dee;
			//dee.x1 = 1000;
			//dee.y1 = 250;
			//dee.x2 = 1500;
			//dee.y2 = 600;

			//g_pDraw->DrawRectangleGradientIn(dee, true, D3DCOLOR_XRGB(255, 255, 255), D3DCOLOR_XRGB(0,0,0), 0.2f, pDevice);

			if (!Interfaces::Engine->IsInGame() && !Interfaces::Engine->IsConnected())
				ImGui::GetIO().MouseDrawCursor = true;
			else
				ImGui::GetIO().MouseDrawCursor = Settings.Menu.MenuOpened;
		ImGui_ImplDX9_NewFrame();
			if (Settings.Menu.MenuOpened)
			{

				GuiVector2 xd;
				xd.y = 500;
				xd.x = 500;


				g_pDraw->DrawCircle(xd , 50, false, D3DCOLOR_XRGB(255, 0, 0), pDevice);

				GuiVector4 lmao;

				lmao.x1 = 250;
				lmao.y1 = 300;
				lmao.x2 = 750;
				lmao.y2 = 500;

				g_pDraw->DrawLine(lmao, D3DCOLOR_XRGB(0, 255, 0), pDevice);


				GuiVector6 ecks;
				ecks.x1 = 100;
				ecks.x2 = 200;
				ecks.x3 = 150;
				ecks.y1 = 200;
				ecks.y2 = 200;
				ecks.y3 = 300;


				g_pDraw->DrawTriangle(ecks, false, D3DCOLOR_XRGB(0, 0, 255), pDevice);

				GuiVector4 dee;
				dee.x1 = 1000;
				dee.y1 = 250;
				dee.x2 = 1500;
				dee.y2 = 600;

				g_pDraw->DrawRectangle(dee, false, D3DCOLOR_XRGB(255, 255, 255), pDevice);

				ImGui::Begin("GetpAyyGooseHookWareTuxBaitGang.cc.pl.net.us.xyz.club.org.team", &Settings.Menu.MenuOpened, ImVec2(928, 400), 1.f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ShowBorders);
				{
					if (ImGui::Button("Aimbot", ImVec2(300.f, 20.f)))
					{
						AimTab = true;
						VisualsTab = false;
						MiscTab = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Visuals", ImVec2(300.f, 20.f)))
					{
						AimTab = false;
						VisualsTab = true;
						MiscTab = false;
					}
					ImGui::SameLine();
					if (ImGui::Button("Misc", ImVec2(300.f, 20.f)))
					{
						AimTab = false;
						VisualsTab = false;
						MiscTab = true;
					}
					float w = ImGui::GetWindowWidth();
					if (AimTab)
					{
						ImGui::Text("Aimbot");
						//ImGui::Text("%f", ImGui::GetWindowWidth());
						ImGui::BeginChild("cAimbot Settings", ImVec2(ImGui::GetWindowWidth() / 2 - 12, 340), true);
						{
							ImGui::Text("Aimbot Settings");
							ImGui::Checkbox("Enabled", &Settings.Aimbot.Enabled);
							ImGui::Combo("Aimbot Mode", &Settings.Aimbot.AimbotMode, "Aim At Bone\0Hitscan\0");
							if (Settings.Aimbot.AimbotMode == 0)
								ImGui::SliderInt("Bone", &Settings.Aimbot.Bone, 0, 100);
							ImGui::Combo("Entity Checks", &Settings.Aimbot.EntityChecks, "Visible\0Autowall\0");
							if (Settings.Aimbot.EntityChecks == AUTOWALL)
								ImGui::SliderFloat("Autowall Damage", &Settings.Aimbot.AutowallDamage, 0.1f, 100.f);
							ImGui::Combo("Key", &Settings.Aimbot.Key, Keys, ARRAYSIZE(Keys));
							ImGui::SliderFloat("Fov", &Settings.Aimbot.Fov, 0.f, 360.f);
							if (!Settings.Aimbot.AntiAim)
							{
								ImGui::SliderFloat("Smoothing-Y", &Settings.Aimbot.SmoothY, 1.f, 30.f);
								ImGui::SliderFloat("Smoothing-X", &Settings.Aimbot.SmoothX, 1.f, 30.f);
							}
							ImGui::EndChild();
						}
						ImGui::SameLine();
						ImGui::BeginChild("cAimbot Misc", ImVec2(ImGui::GetWindowWidth() / 2 - 12, 340), true);
						{
							ImGui::Text("Aimbot Misc");
							ImGui::Checkbox("Hitchance", &Settings.Aimbot.HitchanceEnabled);
							if (Settings.Aimbot.HitchanceEnabled)
								ImGui::SliderInt("Hitchance", &Settings.Aimbot.Hitchance, 1, 100);
							ImGui::Checkbox("Prediction", &Settings.Aimbot.EnginePrediction);
							ImGui::Checkbox("AutoShoot", &Settings.Aimbot.AutoShoot);
							ImGui::Checkbox("Silent Aim", &Settings.Aimbot.SilentAim);
							ImGui::Combo("Recoil", &Settings.Aimbot.NoRecoil, "None\0RCS\0No Recoil");
							ImGui::Checkbox("Anti-Unthrusted", &Settings.Aimbot.AntiUntrust); //chill its a meme
							ImGui::Checkbox("AutoStop", &Settings.Aimbot.AutoStop);
							ImGui::Checkbox("AutoCrouch", &Settings.Aimbot.AutoCrouch);
							ImGui::Checkbox("AntiAim", &Settings.Aimbot.AntiAim);
							if (Settings.Aimbot.AntiAim)
							{
								Settings.Aimbot.SmoothY = 1.f;
								Settings.Aimbot.SmoothX = 1.f;
								ImGui::Combo("AntiAim-Yaw", &Settings.Aimbot.AntiAimYaw, "None\0Backwards\0Spin\0Jitter\0Dynamic Jitter\0Right\0Left\0Fake Left\0Fake Right 1\0Fake Right 2\0Fake Forwards\0Fake Jitter 1\0Fake Jitter 2\0Fake Dynamic Jitter\0Fake Backwards 1\0Fake Backwards 2\0Fake Backwards 3\0Fake Static\0");
								ImGui::Combo("AntiAim-Pitch", &Settings.Aimbot.AntiAimPitch, "None\0Down\0Up\0Half Down\0Half Up\0Jitter\0Dynamic Jitter\0Slow Jitter\0");
								if (!Settings.Aimbot.AntiUntrust)
								{
									ImGui::Checkbox("LispY", &Settings.Aimbot.LispY);
									ImGui::Checkbox("LispX", &Settings.Aimbot.LispX);
								}
								else
								{
									Settings.Aimbot.LispY = false;
									Settings.Aimbot.LispX = false;
								}
							}
							ImGui::Checkbox("Resolver", &Settings.Aimbot.Resolver);
							ImGui::Checkbox("Lag Compensation", &Settings.Aimbot.LagCompensation);
							ImGui::EndChild();
						}
					}
					if (VisualsTab)
					{
						ImGui::Text("Visuals");
						ImGui::BeginChild("cVisual ESP", ImVec2(ImGui::GetWindowWidth() / 2 - 12, 340), true);
						{
							ImGui::Text("ESP");
							ImGui::Checkbox("Enbaled", &Settings.Visuals.Enabled);
							ImGui::Checkbox("Player Boxes", &Settings.Visuals.DrawPlayerBoxes);
							ImGui::SameLine();
							ImGui::ColorEdit3("Box Terrorist", Settings.Visuals.BoxColorTerrorist, ImGuiColorEditFlags_NoSliders);
							ImGui::SameLine();
							ImGui::ColorEdit3("Box Counter-Terrorist", Settings.Visuals.BoxColorCounterTerrorist, ImGuiColorEditFlags_NoSliders);
							ImGui::Checkbox("Player Name", &Settings.Visuals.DrawName);
							ImGui::Checkbox("Player Weapon", &Settings.Visuals.DrawWeapon);
							ImGui::Combo("Health Bar", &Settings.Visuals.DrawHealthBar, "None\0Left\0");
							ImGui::Combo("Armor Bar", &Settings.Visuals.DrawArmorBar, "None\0Right\0");
							ImGui::SliderFloat("Box Width", &Settings.Visuals.BoxWidth, 0.1f, 10.f);
							ImGui::Checkbox("Glow", &Settings.Visuals.Glow);
							ImGui::SameLine();
							ImGui::ColorEdit3("Glow Terrorist", Settings.Visuals.GlowColorTerrorist, ImGuiColorEditFlags_NoSliders);
							ImGui::SameLine();
							ImGui::ColorEdit3("Glow Counter-Terrorist", Settings.Visuals.GlowColorCounterTerrorist, ImGuiColorEditFlags_NoSliders);
							ImGui::Text("Chams");
							ImGui::Checkbox("Chams", &Settings.Visuals.Chams);
							if (Settings.Visuals.Chams) {
								ImGui::Combo("Visual Style", &Settings.Visuals.VisualStyle, "Textured\0Flat\0WireFramed\0");
								ImGui::ColorEdit3("Chams Terrorist Visual", Settings.Visuals.ChamsColorTerroristVisual, ImGuiColorEditFlags_NoSliders);
								ImGui::ColorEdit3("Chams Counter-Terrorist Visual", Settings.Visuals.ChamsColorCounterTerroristVisual, ImGuiColorEditFlags_NoSliders);
								ImGui::Checkbox("Ignore Z Buffer", &Settings.Visuals.IgnoreZ);
								if (Settings.Visuals.IgnoreZ) {
									ImGui::Combo("Ignore Z Style", &Settings.Visuals.IgnoreZStyle, "Textured\0Flat\0WireFramed\0");
									ImGui::ColorEdit3("Chams Terrorist Ignore Z", Settings.Visuals.ChamsColorTerroristIgnoreZ, ImGuiColorEditFlags_NoSliders);
									ImGui::ColorEdit3("Chams Counter-Terrorist Ignore Z", Settings.Visuals.ChamsColorCounterTerroristIgnoreZ, ImGuiColorEditFlags_NoSliders);
								}
							}
							ImGui::EndChild();
						}
						ImGui::SameLine();
						ImGui::BeginChild("cVisual Viewmodel", ImVec2(ImGui::GetWindowWidth() / 2 - 12, 340), true);
						{
							ImGui::Text("Viewmodel");
							ImGui::SliderFloat("Viewmodel Fov", &Settings.Visuals.ViewModelFov, -180.f, 180.f);
							ImGui::Checkbox("No Visual Recoil", &Settings.Visuals.NoVisRecoil);
							if (Settings.Visuals.NoVisRecoil)
								ImGui::SliderFloat("AimPunch Factor", &Settings.Visuals.AimPunchFactor, 0.f, 100.f);
							ImGui::Checkbox("Custom Players (Check before ingame)", &Settings.Visuals.CustomPlayers);
							ImGui::Checkbox("Custom Gloves (Check before ingame)", &Settings.Visuals.CustomGloves);
							ImGui::SliderFloat("Thirdperson", &Settings.Visuals.ThirdPerson, 0.f, 1000.f);
							ImGui::EndChild();
						}
					}
					if (MiscTab)
					{
						ImGui::Text("Misc"); ImGui::BeginChild("cMisc Main", ImVec2(ImGui::GetWindowWidth() / 3 - 12, 340), true);
						{
							ImGui::Checkbox("Bunnyhop", &Settings.Misc.Bunnyhop);
							ImGui::Combo("Autostrafe Mode", &Settings.Misc.AutoStrafe, "None\0Normal\0Silent\0Rage\0");
							ImGui::Checkbox("NameSpammer", &Settings.Misc.NameSpam);
							ImGui::Checkbox("NameStealer", &Settings.Misc.NameStealer);
							ImGui::EndChild();
						}
						ImGui::SameLine();
						ImGui::BeginChild("cMisc Alt", ImVec2(ImGui::GetWindowWidth() / 3 - 12, 340), true);
						{
							ImGui::Checkbox("FakeLag", &Settings.Misc.FakeLag);
							if (Settings.Misc.FakeLag)
								ImGui::SliderInt("FakeLag Amount", &Settings.Misc.FakeLagAmount, 0, 15);
							ImGui::EndChild();
						}
						ImGui::SameLine();
						ImGui::BeginChild("cMisc Config", ImVec2(ImGui::GetWindowWidth() / 3 - 12, 340), true);
						{
							std::vector<std::string> FilesInDir = g_Config.GetAllConfigs("C:\\GooseHook");
							for (int i = 0; i < FilesInDir.size(); i++)
								ImGui::Text(FilesInDir[i].c_str());

							ImGui::InputText("Config Name", Settings.Misc.ConfigBuffer, MAX_PATH);
							if (ImGui::Button("Save Config"))
								g_Config.CreateConfig("C:\\GooseHook", Settings.Misc.ConfigBuffer);
							ImGui::SameLine();
							if (ImGui::Button("Load Config"))
								g_Config.LoadConfig(Settings.Misc.ConfigBuffer);
							ImGui::SameLine();
							if (ImGui::Button("Delete Config"))
								g_Config.DeleteConfig(Settings.Misc.ConfigBuffer);
							ImGui::EndChild();
						}
						
					}

				}
				ImGui::End();
			}
			ImGui::Render();
		}
	return EndScene_Original(pDevice);
}

HRESULT __stdcall Hooks::Reset_Hooked(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam)
{
	if (!Initialized) return ResetScene_Original(pDevice, pPresParam);
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto newr = 
	ImGui_ImplDX9_CreateDeviceObjects();
	return ResetScene_Original(pDevice, pPresParam);
}	

void GUI_Init(IDirect3DDevice9* pDevice)
{
	ImGui_ImplDX9_Init(Window, pDevice);
	auto& style = ImGui::GetStyle();

	int width2, height2, bytes_per_pixel;
	unsigned char* pixels;
	//ImGuiStyle * style = &ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();
	/*comicsans = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\tahoma.ttf", 12);
	comicsansbig = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\tahoma.ttf", 24);*/
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width2, &height2, &bytes_per_pixel);
	//tahoma_compressed_data_base85
	g_FontTexture = NULL;

	pDevice->CreateTexture(width2, height2, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_FontTexture, NULL);
	D3DLOCKED_RECT tex_locked_rect;
	g_FontTexture->LockRect(0, &tex_locked_rect, NULL, 0);

	for (int y = 0; y < height2; y++)
		memcpy((unsigned char *)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixels + (width2 * bytes_per_pixel) * y, (width2 * bytes_per_pixel));
	g_FontTexture->UnlockRect(0);

	// Store our identifier
	io.Fonts->TexID = (void *)g_FontTexture;
	style.WindowMinSize = ImVec2(115, 20);
	style.FramePadding = ImVec2(4, 0);
	style.ItemSpacing = ImVec2(5, 2);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.Alpha = 1.f;
	style.WindowRounding = 0.0f;
	style.WindowPadding = ImVec2(9, 8);
	style.FrameRounding = 0.f;
	style.IndentSpacing = 5.f;
	style.ItemInnerSpacing = ImVec2(2, 4);
	style.WindowTitleAlign = ImGuiAlign_Center;
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 0.0f;
	style.ScrollbarSize = 5.0f;
	style.ScrollbarRounding = 0.f;

	style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.2f);
	style.Colors[ImGuiCol_Border] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.08f, 0.69f, 0.02f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.00f, 0.76f, 0.04f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.47f, 0.77f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.55f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.71f, 0.01f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.05f, 0.64f, 0.01f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.04f, 0.70f, 0.02f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.02f, 0.57f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.22f, 0.27f, 1.00f);

	Initialized = true;
}
