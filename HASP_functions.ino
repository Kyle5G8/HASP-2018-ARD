bool exprun = false;
void hasp_processcmd(byte Serialin)
{
    if(Serialin == 0x01)//spectrometer on
    {
      spectrometeron();
    }
    if(Serialin == 0x02)//spectrometer off
    {
      spectrometeroff();
    }
    if(Serialin == 0x03)//Light on
    {
      lighton();
    }
    if(Serialin == 0x04)//Light off
    {
      lightoff();
    }
    if(Serialin == 0x05)//fan on
    {
      fanon();
    }
    if(Serialin == 0x06)//fan off
    {
      fanoff();
    }
    if(Serialin == 0x07)//open valve
    {
      valveopen();
    }
    if(Serialin == 0x08)//close valve
    {
      valveclose();
    }
    if(Serialin == 0x09)//Pump on
    {
      pumpon();
    }
    if(Serialin == 0x10)//pump off
    {
      pumpoff();
    }
    if(Serialin == 0x11)//experiment
    {
      exprun = true;
    }
}

void spectrometeron()
{
  //in this and the following functions, write the code for the digital pin actions to enact command
}

void spectrometeroff()
{
  
}

void lighton()
{
  
}

void lightoff()
{
  
}

void fanon()
{
  
}

void fanoff()
{
  
}

void valveopen()
{
  
}

void valveclose()
{

}

void pumpon()
{
  
}

void pumpoff()
{
  
}

bool experiment()
{
  return exprun;
}

