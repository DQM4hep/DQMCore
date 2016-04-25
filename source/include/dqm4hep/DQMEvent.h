  /// \file DQMEvent.h
/*
 *
 * DQMEvent.h header template automatically generated by a class generator
 * Creation date : jeu. mars 26 2015
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMEVENT_H
#define DQMEVENT_H

// -- dqm4hep headers
#include "dqm4hep/DQM4HEP.h"

namespace dqm4hep
{

template <typename T>
class DQMEventBase;

/** DQMEvent class.
 *
 *  Main interface to a monitored event through the framework.
 *  This class is passed to modules in order to monitor its contents.
 *  The real data structure can be accessed via the getEvent methods
 *  which convert the interface into a DQMEventBase (see below).
 *
 *  To define an event, the user should always inherits the DQMEventBase class
 *  in order to have valid operations.
 */ 
class DQMEvent
{
public:
	/** Destructor
	 */
	virtual ~DQMEvent();

	/** Returns the event converted to asked type
	 */
	template <typename T>
	T *getEvent() const;

	/** Set the event.
	 *
	 *  The dqm event can own the wrapped event
	 *  is the second arguement is set to true
	 */
	template <typename T>
	void setEvent(T *pEvent, bool isOwner = true);

	/** Clear the event (normally delete the event structure)
	 */
	template <typename T>
	void clear();

	/** Whether the dqm event is the owner of the wrapped event
	 */
	bool isOwner() const;

	/** Set the event size as read by the socket (unit in bytes)
	 */
	void setEventSize(uint64_t eventSize);

	/**
	 */
	uint64_t getEventSize() const;

protected:
	/** Private constructor
	 */
	DQMEvent();

protected:
	bool            m_isOwner;
	uint64_t        m_size;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template <typename T>
class DQMEventBase : public DQMEvent
{
public:
	/** Destructor
	 */
	virtual ~DQMEventBase();

	/** Returns the stored event
	 */
	virtual T *getEvent() const = 0;

	/** Set the handled event
	 */
	virtual void setEvent(T *pEvent) = 0;

	/** Clear the handler by deleting the handled event
	 */
	virtual void clear() = 0;
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

inline DQMEvent::DQMEvent() :
		m_isOwner(true),
		m_size(0)
{
}

//-------------------------------------------------------------------------------------------------

inline DQMEvent::~DQMEvent()
{
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline T *DQMEvent::getEvent() const
{
	const DQMEventBase<T> *pBaseEvent = dynamic_cast<const DQMEventBase<T>*>(this);

	if(NULL == pBaseEvent)
		return 0;

	return pBaseEvent->getEvent();
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline void DQMEvent::setEvent(T *pEvent, bool isOwner)
{
	DQMEventBase<T> *pBaseEvent = dynamic_cast<DQMEventBase<T>*>(this);

	if(NULL == pBaseEvent)
		return;

	pBaseEvent->setEvent(pEvent);
	m_isOwner = isOwner;
}

//-------------------------------------------------------------------------------------------------

template <typename T>
inline void DQMEvent::clear()
{
	if(m_isOwner)
	{
		DQMEventBase<T> *pBaseEvent = dynamic_cast<DQMEventBase<T>*>(this);

		if(NULL == pBaseEvent)
			return;

		pBaseEvent->clear();
	}

	m_size = 0;
}

//-------------------------------------------------------------------------------------------------

inline bool DQMEvent::isOwner() const
{
	return m_isOwner;
}

//-------------------------------------------------------------------------------------------------

inline void DQMEvent::setEventSize(uint64_t eventSize)
{
	m_size = eventSize;
}

//-------------------------------------------------------------------------------------------------

inline uint64_t DQMEvent::getEventSize() const
{
	return m_size;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

template <typename T>
inline DQMEventBase<T>::~DQMEventBase()
{
}

} 

#endif  //  DQMEVENT_H
