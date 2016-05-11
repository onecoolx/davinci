#include <stdio.h>
#include "davinci.h"

using namespace davinci;

int main(int, char*[])
{
    WebSize size(800, 600);
    WebViewClient * client = new WebViewClient();

    WebView* view = new WebView(*client, size);



    delete view;
    delete client;
    return 0;
}
