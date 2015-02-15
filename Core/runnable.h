#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <atomic>
#include <thread>

/** Runnable base class
Classes implementing this must override Run(), and can override HandleStop() and ~Runnable() would they need to handle exception at stop.
Implemented class must stop as soon as possible when m_stop = true. They are also warned of this status change with HandleStop(). 
*/
class Runnable
{
public:
    Runnable() : m_stop(false), m_thread() { }
    //! Destructor. Stops the thread before exiting. Can be overwritten.
    virtual ~Runnable() { try { Stop(); } catch(...) { /*??*/ } }

    //disable copy constructors
    Runnable(Runnable const&) = delete;
    Runnable& operator =(Runnable const&) = delete;

    /** Tells the runnable object to stop.
    * This function only returns when the thread has exited. 
    */
    void Stop() { m_stop = true; HandleStop(); m_thread.join(); }
    /** Tells the runnable object to start the thread, calling the Run function. 
    */
    void Start() { m_thread = std::thread(&Runnable::Run, this); }

protected:
    /** This is called when Stop() is called, so you may do specifics actions at this time. 
    * Prefer using this instead of a loop checking the m_stop status at all time.
    */
    virtual void HandleStop() {}
    /** main thread function, called with Start(). 
    * Run() must stop itself when m_stop go true.
    */
    virtual void Run() = 0;

    //! Indicate wether the thread should be stopping.
    std::atomic<bool> m_stop;

private:
    std::thread m_thread;
};

#endif //RUNNABLE_H