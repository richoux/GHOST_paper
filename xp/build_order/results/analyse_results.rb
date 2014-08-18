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
lines = 0
time_ref = 0
cost = 0

# For each line in file
file.each do |line|
  words = line.split(': ')
  if words[0].include? "Global cost"
    if words[1].to_i == 0
      count += 1
    end
    lines += 1
  elsif words[0].include? "Optimization cost"
    if not words[1].include? "2.14748"
      cost += words[1].to_i
    end
  elsif words[0].include? "Time reference"
    time_ref = words[1].to_i
  end
end

mean = (cost.to_f / count).round(1)
gain = (time_ref - mean).round(1)

puts "#{ARGV[0]}: #{count}/#{lines}, ref=#{time_ref}, ghost=#{mean}, gain=#{gain}"

exit
