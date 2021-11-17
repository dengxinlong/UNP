void
Pthread_mutex_lock(pthread_mutex_t * mptr)
{
    int ret;
    
    if ( !(ret = pthread_mutex_lock(mptr)) )
        return;
    errno = ret;
    err_sys("pthread_mutex_lock error");
}