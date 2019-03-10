#!/bin/sh
for file in ./parser_test/*
do
	value=`cat $file`
	(>&2 printf "$file: ")
	echo "$value" | ./lem-in
done
