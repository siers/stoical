#!/usr/bin/env ruby

ENDIAN = :little

class String
  def address
    bytes = scan(/../).map { |x| x.to_i(16).chr }
    bytes.reverse! if ENDIAN == :little
    bytes.join.binarize
  end

  def binarize
    force_encoding("BINARY")
  end
end

contents = File.open('bin/stub.bin.tmpl').read.binarize

ARGV.each_slice(2) do |src, dst|
  # puts({src => src.address, dst => dst.address}.inspect)
  3.times do
    contents.gsub!(src.address, dst.address)
  end
end

File.open('stub', 'w').write(contents)

# usage:
# ./prepare_stub[ 0xswapable 0xrealaddr]*
