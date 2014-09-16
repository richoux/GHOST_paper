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
wins = 0
draws = 0
diff = 0
hp = 0
me = false

# For each line in file
file.each do |line|
  if line.include? "#"
    next
  end

  if line.include? "Draw"
    draws += 1
    total += 1
    next
  end

  words = line.split(': ')
  if words[0].include? "Winner"
    if words[1].include? "You"
      wins += 1
      me = true
    else
      me = false
    end

    total += 1
  elsif words[0].include? "Diff"
    diff += words[1].to_i
  elsif words[0].include? "HP" and me
    hp += words[1].to_f
  end
end

mean = (diff.to_f / total).round(1)
mean_hp = (hp / total).round(1)
percent = (100 * wins.to_f / total).round(1)

puts "#{ARGV[0]}:\n   #{percent}\% of wins (#{wins}/#{total}, #{draws} draws)"
puts "   Average diff = #{mean}"
if not hp == 0
  puts "   Average HP = #{mean_hp}"
end

exit
