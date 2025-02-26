#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "newlines.h"
#include "colors.h"

int distro;

char pkgs[200];
char cmd[225];

void setupArch() {
	/* PS1 */
	system("echo \"PS1='\\w \$ '\" >> ~/.bashrc");
	
	/* Packages and Updates */
	system("pacman -Syu git base-devel flatpak gimp htop vlc wget --noconfirm");
	
	/* Paru setup */
	system("git clone https://aur.archlinux.org/paru-bin.git");
	system("cd paru-bin");
	system("makepkg -si");
	
	/* Virtualbox setup */
	system("pacman -S virtualbox virtualbox-host-modules-arch --noconfirm");
	
	/* User packages */
	system(cmd);
	
	printf("Setup complete! Rebooting.");
	sleep(2);
	system("reboot");
}

void setupDebian() {
	/* PS1 */
	system("echo \"PS1='\\w \$ '\" >> ~/.bashrc");
	
	/* Updates */
	system("apt update && apt upgrade -y");
	
	/* Packages */
	system("apt install -y nala git flatpak gimp htop vlc wget");
	
	/* Virtualbox setup */
	system("wget https://download.virtualbox.org/virtualbox/7.1.6/virtualbox-7.1_7.1.6-167084~Debian~bookworm_amd64.deb");	
	system("dpkg -i virtualbox-*");
	system("apt install -f -y");
	
	/* User pkgs */
	system(cmd);
	
	/* Flathub setup */
	system("flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo");
	
	printf("Setup complete! Rebooting.");
	sleep(2);
	system("reboot");
}

void setupFedora() {
	/* PS1 */
	system("echo \"PS1='\\w \$ '\" >> ~/.bashrc");
	
	/* Updates */
	system("dnf upgrade -y --refresh");
	
	/* Packages */
	system("dnf install -y git gimp htop vlc wget");
	
	/* Virtualbox setup */
	system("wget https://download.virtualbox.org/virtualbox/7.1.6/VirtualBox-7.1-7.1.6_167084_fedora40-1.x86_64.rpm");	
	system("dnf install -y virtualbox-*");
	
	/* User pkgs */
	system(cmd);
	
	printf("Setup complete! Rebooting.");
	sleep(2);
	system("reboot");
}

void archPkgs() {
	printf("Any additional packages you want to install? (make sure they are in the repos): " NL);
	scanf("%[^\n]", pkgs);
	getchar();
	snprintf(cmd, sizeof(cmd), "pacman -S %s --noconfirm", pkgs);
	
	setupArch();
}
		
void debianPkgs() {
	printf("Any additional packages you want to install? (make sure they are in the repos): " NL);
	scanf("%[^\n]", pkgs);
	getchar();
	snprintf(cmd, sizeof(cmd), "apt install -y %s", pkgs);
	
	setupDebian();
}

void fedoraPkgs() {
	printf("Any additional packages you want to install? (make sure they are in the repos): " NL);
	scanf("%[^\n]", pkgs);
	getchar();
	snprintf(cmd, sizeof(cmd), "dnf install -y %s", pkgs);
	
	setupFedora();
}

void inputEval() {
	if (distro == 1) {
		archPkgs();
	} else if (distro == 2) {
		debianPkgs();
	} else if (distro == 3) {
		fedoraPkgs();
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

	printf(RESET "3) ");
	printf(BLUB "Fedora" NL);

    printf(RESET "> ");
    scanf(" %d", &distro); 
    getchar();

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
