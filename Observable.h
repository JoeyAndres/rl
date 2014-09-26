/* 
 * File:   Observable.h
 * Author: jandres
 *
 * Created on June 2, 2014, 3:25 PM
 */

#ifndef OBSERVABLE_H
#define	OBSERVABLE_H

#include <vector>

#include "Observer.h"

using std::vector;

template <class NotifyArgument>
class Observable {
public:
    Observable();
    virtual ~Observable();

    bool registerObserver(Observer<NotifyArgument>& observable);
    bool removeObserver(Observer<NotifyArgument>& observable);
    void notifyObserves(NotifyArgument& arg);
private:
    vector<Observer<NotifyArgument>& > _observers;
};

template <class NotifyArgument>
bool Observable<NotifyArgument>::registerObserver(Observer<NotifyArgument>& observable) {

}

template <class NotifyArgument>
bool Observable<NotifyArgument>::removeObserver(Observer<NotifyArgument>& observable) {

}

template <class NotifyArgument>
bool Observable<NotifyArgument>::notifyObserves(NotifyArgument& arg) {
    for (Observer<NotifyArgument>& observer : _observers) {
        observer.notify(arg);
    }
}

#endif	/* OBSERVABLE_H */

