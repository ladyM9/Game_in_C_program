#ifndef __DEFINES_H__
#define __DEFINES_H__

class OBJECT
{
    private:
        int x = 2;
        int y = 3;
        int xOld;
        int yOld;
        int r = 2;
        int o = 2*r*3.14;
    public:
        void funkcija(int &a, int &b, int &aOld, int &bOld, int &R, int &O)
        {
            x = a;
            y = b;
            xOld = aOld;
            yOld = bOld;
            r = R;
            o = O;

        }
};
#endif