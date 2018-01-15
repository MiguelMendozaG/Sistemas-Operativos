#include<stdlib.h>
#include<unistd.h>   //sleep(seconds)
int main()
{
  system("dbus-send --system --print-reply --dest=org.freedesktop.login1 /org/freedesktop/login1 \"org.freedesktop.login1.Manager.PowerOff\" boolean:true");
  retrun 0;
}
