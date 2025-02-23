#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "newlines.h"
#include "colors.h"

int distro;

void setupArch() {
}

void setupDebian() {
	/* PS1 */
	system("echo \"PS1='\\w \$ '\" >> ~/.bashrc");
	
	/* Packages */
	system("apt install -y nala git flatpak gimp htop vlc wget");
	
	/* Virtualbox setup */
	system("wget https://download.virtualbox.org/virtualbox/7.1.6/virtualbox-7.1_7.1.6-167084~Debian~bookworm_amd64.deb");	
	system("dpkg -i virtualbox-*");
	system("apt install -f -y");
	
	/* Flathub setup */
	system("flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo");
	/* Cool apps (uncomment the ones you need) */
	// system("flatpak install flathub dev.vencord.Vesktop");
	// system("flatpak install flathub org.libretro.RetroArch");
	// system("flatpak install flathub org.DolphinEmu.dolphin-emu");
	
	system("reboot");
}

void inputEval() {
	if (distro == 1) {
		setupArch();
	} else if (distro == 2) {
		setupDebian();
	} else {
		printf(RED "Invalid input!");
	}
}

void input() {
    printf(RESET "What distro are you on?" NL);

    printf(RESET "1) ");
    printf(CYNB "Arch" NL);

    printf(RESET "2) ");
    printf(DEB "Debian" NL);

    printf(RESET "> ");
    scanf(" %d", &distro); 
    
    inputEval();
    system("clear");
}

int main() {
	printf(RED "MAKE SURE YOU ARE RUNNING THIS PROGRAM AS ROOT!" NL);
	sleep(1);
	system("clear");
    printf(MAGB BYEL "  Lessential  " NL2);
    usleep(500000);
    input();

    return 0;
}
