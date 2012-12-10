#!/usr/bin/env ruby

class String
  def address
    scan(/../).map { |x| x.to_i(16).chr }.join.binarize
  end

  def binarize
    force_encoding("BINARY")
  end
end

contents = File.open('bin/stub.bin.tmpl').read.binarize

ARGV.each_slice(2) do |src, dst|
  p src.address, dst.address
  contents.sub!(src.address, dst.address)
end

File.open('stub', 'w').write(contents)
