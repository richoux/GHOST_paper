#!/usr/bin/ruby

def usage
  puts  "Usage: " + $0 + " FILE"
end

# We must have at least a file name
if ARGV.length == 0
  usage
  exit
end

file = File.open(ARGV[0])

count = 0
gain = 0

# For each line in file
file.each do |line|
  words = line.split(', ')
  gains = words[3].split('=')
  gain += gains[1].to_i
  count += 1
end

mean = (gain.to_f / count).round(2)
  
puts "Average for #{ARGV[0]}: #{mean}"

exit
