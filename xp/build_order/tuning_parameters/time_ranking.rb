#!/usr/bin/ruby

def usage
  puts "#{$0}"
  puts  "Usage: " + $0 + " FILE"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

# Open file
file = File.open(ARGV[0])

count = 0
total = 0
found = false; 
opt = Array.new

# For each line in file
file.each do |line|
  words = line.split(': ')
  if words[0].include? "Global cost"
    if words[1].to_i == 0
      found = true;
    else
      found = false;
    end
    total += 1
  end
  if words[0].include? "Optimization cost" and found
    opt.push words[1].chomp + " " + words[0]
    count += 1
  end
end

opt.sort!

puts "#{count} / #{total}"
puts opt

exit
