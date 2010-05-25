// Copyright (c) 2009 Ryan Seal <rlseal -at- gmail.com>
//
// This file is part of Bit Pattern Generator (BPG) Software.
//
// BPG is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// BPG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BPG.  If not, see <http://www.gnu.org/licenses/>.
#include "TestCommand.hpp"
#include <bpg-v2/Common/Timer.hpp>
#include <boost/shared_ptr.hpp>

using namespace std;

int main()
{
   // timeout value in seconds
   const unsigned int TIME_OUT = 3;

   boost::shared_ptr<Command> command = 
      boost::shared_ptr<TestCommand>(new TestCommand());

   Timer timer(TIME_OUT);
   timer.Register(command);

   cout << "start system" << endl;
   timer.Start();
   timer.Wait();

   return 0;
}

