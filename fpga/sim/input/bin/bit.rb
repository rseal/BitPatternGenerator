#!/usr/bin/ruby

def PrintBits(data, bits, file)
  bits = bits - 1
  bits.downto(0) { |x| file.print data[x] }
end

file = File.new("../data/radarTb.vec", 'w')

bits      = 16
numStates = 200
rotations = 75
clkDiv    = 2
count1    = 0
count2    = 0
count3    = 1
duration  = Array.new(numStates)  {|i| i+1}
states    = Array.new(numStates) {|i| i}
bufferLength = 4096
padding = bufferLength - numStates*2

#repeat mode creation twice for 2 identical modes
4.downto(1){ 
  
  #create identical buffers for porta and portb
#  2.downto(1){

    #create the buffer states
    numStates.downto(1) {   
      PrintBits(duration[count1],bits,file)
      file.puts
      PrintBits(states[count1],bits,file) 
      file.puts
      count1 += 1
      count2 += 2 
    }
    count1 = 0
    
    #loading data into the FPGA requires a fixed size of 4096 16-bit words
    #padding is required for shorter buffers 
    padding.downto(1) {
      15.downto(0) {
	file.print 0
      }
      file.puts
      count2 += 1
    }
  #}

  #create variables for porta and portb
  #these variables control the clock and indexing of the state data
  #2.downto(1){
    PrintBits(numStates, bits,file)
    file.puts
    PrintBits(rotations, bits,file) 
    file.puts
    PrintBits(clkDiv, bits,file)
    file.puts
  #}

  #++count3
}

puts "#{count2} 16-bit elements created"

