#pragma once
class BaseGame
{
public:

   BaseGame(void)
      : m_bIsPaused( false )
   {
   }

   virtual void update() = 0;
   virtual void render() = 0;
   virtual void paused() = 0;
   bool isPaused() const { return m_bIsPaused; };
   bool togglePause(){ m_bIsPaused = !m_bIsPaused; }

private :
   bool m_bIsPaused;

};

