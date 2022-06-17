//encoding=GBK
//傻逼C在Windows不按UTF-8编码，而是按ANSI编码，傻逼，搞得我在VSCode里要设置编码才行
#include "UIPrint.h"
int main() {
    UI_Welcome();
    system("pause>nul");//没办法，先这样吧
    return 0;
}