#include <iostream>
#include <Windows.h>


#define POLL_RATE 100

#define GAME_WIN_NAME "Call of Duty\xAE"

#define HEALTH 0X0176C8B8
#define POINTS 0x018EF124

#define PLAYER_X 0x018ED088
#define PLAYER_Y 0x018ED08C
#define PLAYER_Z 0x018ED090

#define COLT_M1911_AMMO 0x018ED1FC
#define COLT_M1911_CLIP 0x018ED67C
#define GRANADES 0x018ED674
#define GEWEHR_CLIP 0x018ED69C
#define KAR98K_CLIP 0x018ED66C

void tp2pack(HANDLE process_handle) {
    float cords_X = -52;
    float cords_Y = 540;
    float cords_Z = 101;

    WriteProcessMemory(process_handle, (LPVOID)PLAYER_X, &cords_X, sizeof(cords_X), NULL);
    WriteProcessMemory(process_handle, (LPVOID)PLAYER_Y, &cords_Y, sizeof(cords_X), NULL);
    WriteProcessMemory(process_handle, (LPVOID)PLAYER_Z, &cords_Z, sizeof(cords_X), NULL);
}

void tp2power(HANDLE process_handle) {
    float cords_X = 528;
    float cords_Y = -1794;
    float cords_Z = 58;

    WriteProcessMemory(process_handle, (LPVOID)PLAYER_X, &cords_X, sizeof(cords_X), NULL);
    WriteProcessMemory(process_handle, (LPVOID)PLAYER_Y, &cords_Y, sizeof(cords_X), NULL);
    WriteProcessMemory(process_handle, (LPVOID)PLAYER_Z, &cords_Z, sizeof(cords_X), NULL);
}

int main()
{
    std::cout << "Looking for game...\n";
    HWND handle_to_game = NULL;
    while (handle_to_game == NULL) {
        handle_to_game = FindWindowA(NULL, GAME_WIN_NAME);
    }
    std::cout << "Found Game Window.\n";

    DWORD processID;
    GetWindowThreadProcessId(handle_to_game, &processID);
    if (processID != NULL) {
    std::cout << "Found ProcessID";
    }
    else if (processID != NULL || processID == 0)
    {
        std::cout << "Couldn't get ProcessID!";
        exit(1);
    }

    HANDLE process_handle;
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if (process_handle != NULL) {
        std::cout << "Connected!";
    }
    else {
        std::cout << "Failed To Connecto Process";
        exit(1);
    }

    bool modhealth = false;
    bool modpoints = false;
    bool UnlimitedAmmoStartingRoomWeapons = false;

    bool update_screen = true;

    float player_X = 0;
    float player_Y = 0;
    float player_Z = 0;

    while (true) {
        if (update_screen) {
            system("cls");
            std::cout << "Call of Duty World At War Memory Hacker V1" << std::endl;
            std::cout << "==========================================\n";
            std::cout << " [F1] - (" << (modhealth ? "on " : "off") << ") Unlimited Health\n";
            std::cout << " [F2] - (" << (modpoints ? "on " : "off") << ") Set Points to 100K\n";
            std::cout << " [F3] - (" << (UnlimitedAmmoStartingRoomWeapons ? "on " : "off") << ") Unlimited Ammo Starting Room Weapons and Granades\n";
            std::cout << " [F4] - TP To Packapunch\n";
            std::cout << " [F5] - TP To Power\n";
            std::cout << "==========================================\n";
            std::cout << "X: [" << (player_X) << "] ";
            std::cout << "Y: [" << (player_Y) << "] ";
            std::cout << "Z: [" << (player_Z) << "]\n";
            std::cout << "==========================================\n";
            update_screen = false;
        }

        SHORT keypress;

        // modhealth
        keypress = GetAsyncKeyState(VK_F1);
        if (keypress) {
            modhealth = !modhealth;
            update_screen = true;
        }

        // modpoints
        keypress = GetAsyncKeyState(VK_F2);
        if (keypress) {
            modpoints = !modpoints;
            update_screen = true;
        }

        // modammow_M1911_AMMO
        keypress = GetAsyncKeyState(VK_F3);
        if (keypress) {
            UnlimitedAmmoStartingRoomWeapons = !UnlimitedAmmoStartingRoomWeapons;
            update_screen = true;
        }


        keypress = GetAsyncKeyState(VK_F4);
        if (keypress) {
            tp2pack(process_handle);
        }

        keypress = GetAsyncKeyState(VK_F5);
        if (keypress) {
            tp2power(process_handle);
        }


        if (modhealth) {
            int value = 100000;
            WriteProcessMemory(process_handle, (LPVOID)HEALTH, &value, sizeof(value), NULL);
        }

        if (modpoints) {
            int value = 100000;
            WriteProcessMemory(process_handle, (LPVOID)POINTS, &value, sizeof(value), NULL);
        }

        if (UnlimitedAmmoStartingRoomWeapons) {
            int value = 100000;
            WriteProcessMemory(process_handle, (LPVOID)COLT_M1911_AMMO, &value, sizeof(value), NULL);
            WriteProcessMemory(process_handle, (LPVOID)COLT_M1911_CLIP, &value, sizeof(value), NULL);
            WriteProcessMemory(process_handle, (LPVOID)GRANADES, &value, sizeof(value), NULL);
            WriteProcessMemory(process_handle, (LPVOID)GEWEHR_CLIP, &value, sizeof(value), NULL);
            WriteProcessMemory(process_handle, (LPVOID)KAR98K_CLIP, &value, sizeof(value), NULL);
        }

        float x, y, z;
        player_X = ReadProcessMemory(process_handle, (LPVOID)PLAYER_X, &x, sizeof(float), NULL);


        Sleep(POLL_RATE);

        
    }
    
}
