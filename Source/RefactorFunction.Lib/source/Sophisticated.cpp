
static int calc_dpt;
static bool calc_cpt;

void CalcIni(int dpt, bool cpt)
{
    calc_dpt = dpt;
    calc_cpt = cpt;
}

int Calc(bool rcvck)
{
    if (calc_cpt)
    {  return 3; }
    return (rcvck ? 23 : 5);
}
