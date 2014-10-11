/* 
 * File:   Observer.h
 * Author: jandres
 *
 * Created on June 2, 2014, 3:25 PM
 */

#ifndef OBSERVER_H
#define	OBSERVER_H

template<class NotifyArgument>
class Observer {
 public:
  Observer();
  virtual ~Observer();

  virtual void notify(NotifyArgument arg) = 0;
 private:

};

template<class NotifyArgument>
Observer<NotifyArgument>::Observer() {
}

template<class NotifyArgument>
Observer<NotifyArgument>::~Observer() {
}

#endif	/* OBSERVER_H */

