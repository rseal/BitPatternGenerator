#!/usr/bin/ruby

def PrintBits(data, bits, file)
  bits = bits - 1
  bits.downto(0) { |x| file.print data[x] }
end

if ARGV.size < 2
  STDERR.print <<EOF
  Usage: ruby <input file> <outputfile>
EOF
  exit(1)
end

inputFile = File.new(ARGV[0],'r');
outputFile = File.new(ARGV[1],'w');

count = 0;
while line = inputFile.gets
  PrintBits(line.to_i,16,outputFile);
  outputFile.puts "\n";
  count=count +1;
end

puts "successfully wrote #{count} integers to #{ARGV[1]}"
