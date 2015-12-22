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

total = 0
dps = 0
max = 0

# For each line in file
file.each do |line|
  words = line.split(' : ')
  if words[0].include? "DPS"
    #if words[1].include? "4916.36"
    if words[1].include? "6632.73"
    #if words[1].include? "11400"
      max += 1
    end
    dps += words[1].to_i
    total += 1
  end
end

mean_dps = (dps.to_f / total).round(1)
percent = (100 * max.to_f / total).round(1)

puts "#{ARGV[0]}:\n   #{percent}\% of perfects (#{max}/#{total})"
puts "   Average dps = #{mean_dps}"

exit
