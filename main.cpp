#include <Windows.h>
#include <powrprof.h>
#include <iostream>
#include <string>

#pragma comment(lib,"ntdll.lib")
#pragma comment(lib,"Powrprof.lib")

typedef struct _SYSTEM_POWER_INFORMATION {
    ULONG MaxIdlenessAllowed;
    ULONG Idleness;
    LONG TimeRemaining;
    UCHAR CoolingMode;
} SYSTEM_POWER_INFORMATION, *PSYSTEM_POWER_INFORMATION;

using namespace std;

int main() {
    SYSTEM_POWER_INFORMATION pwInfo;
    CallNtPowerInformation(SystemPowerInformation, NULL, NULL, &pwInfo, sizeof(pwInfo));

    cout << "-----------------------------\n   Power Policy parser   \n-----------------------------\n\n";

    switch (pwInfo.CoolingMode) {
    case 0:
        cout << "[+] Cooling mode active" << endl;
        break;
    case 2:
        cout << "[-] The system does not support CPU throttling, or there is no thermal zone defined in the system." << endl;
        break;
    case 1:
        cout << "[*] The system is currently in Passive cooling mode." << endl;
        break;
    
    default:
        cout << "Not Expected" << endl;
        break;
    }
    
    POWER_POLICY pwPolicy;
    GLOBAL_POWER_POLICY pwGlPolicy;

    GetCurrentPowerPolicies(&pwGlPolicy, &pwPolicy);

    printf("[*] The video turn off after -> %lu seconds or %lu minutes\n",pwPolicy.user.VideoTimeoutAc,(pwPolicy.user.VideoTimeoutAc)/60);
    printf("[*] Time before power to fixed disk drives is turned off -> %lu seconds or %lu minutes\n", pwPolicy.user.SpindownTimeoutAc,(pwPolicy.user.SpindownTimeoutAc)/60);
    printf("[*] Fan throttle tolerance -> %uc", pwPolicy.user.FanThrottleToleranceAc);

}
