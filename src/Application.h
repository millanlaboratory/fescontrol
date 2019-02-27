/*
    Copyright (C) 2009-2011  EPFL (Ecole Polytechnique Fédérale de Lausanne)
    Julien Rechenmann <julien.rechenmann@epfl.ch>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "FESJsonReader.h"
#include "FESStimulator.h"
#include <iostream>
#include <chrono>

class Application {
public:
	Application(bool verbose);
	virtual ~Application();
	void init(FESStimulator*, FESJsonReader*);
	void start(std::string nFileName);

	FESStimulator* getStimulator(){return stimulator;}
	FESJsonReader* getJsonReader(){return reader;}

protected:
	FESStimulator* stimulator;
	FESJsonReader* reader;
	bool verbose;

	void initStimulator();
	virtual void runApplication();
	void updateStimulator();
	std::chrono::time_point<std::chrono::system_clock, std::chrono::system_clock::duration> previousEpoch;
	bool done;
};
