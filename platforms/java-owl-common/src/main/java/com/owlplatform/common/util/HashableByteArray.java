/*
 * Owl Platform Common Library for Java
 * Copyright (C) 2012 Robert Moore and the Owl Platform
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *  
 * You should have received a copy of the GNU Lesser General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

package com.owlplatform.common.util;

import java.util.Arrays;
/**
 * Simple wrapper class to permit {@code byte[]} as a hashtable key.  
 * 
 * <p>
 * <em>Warning: Changing the backing byte array will NOT change the hash code of this object if it has
 * already been generated.  For this reason it is STRONGLY recommended that the underlying byte array is
 * NOT modified.</em>
 * </p>
 * 
 * Sourced from http://stackoverflow.com/questions/1058149/using-a-byte-array-as-hashmap-key-java
 * 
 * @author <a href="http://stackoverflow.com/users/22656/jon-skeet">Jon Skeet</a>
 * @author Robert Moore II
 *
 */
public class HashableByteArray implements Comparable<HashableByteArray>{

	/**
	 * The bacjubg byte array.
	 */
	private byte[] data;
	
	/**
	 * Returns the backing byte array.  Note that this method returns the actual array, so changes to 
	 * the array WILL change the data in this object, but the hash value WILL NOT CHANGE.
	 * @return the byte array backing this object.
	 */
	public byte[] getData() {
		return this.data;
	}

	/**
	 * The computed hash value for this byte array.
	 */
	private int hashCode = 0;
	
	/**
	 * Creates a new HashableByteArray from the specified {@code byte[]}.
	 * @param data the byte array to back the new object.
	 */
	public HashableByteArray(byte[] data)
	{
		if(data == null)
		{
			throw new IllegalArgumentException("Cannot instantiate a HashableByteArray with a null byte[].");
		}
		this.data = data;
	}
	
	/**
	 * Returns the hash code for the underlying byte array, as generated by {@link Arrays#hashCode(byte[])}. Note that
	 * this method caches the generated hash code after the first call, so changes to the underlying byte array will
	 * not change the hash code of this object.
	 */
	@Override
	public int hashCode()
	{
		if(this.hashCode == 0)
		{
			return this.hashCode = Arrays.hashCode(this.data);
		}
		return this.hashCode;
	}
	
	/**
	 * Compares this HashableByteArray to another object, o.  If {@code o} is also a HashableByteArray, then
	 * the result is the value of {@code Arrays#equals(byte[], byte[])} for the underlying byte arrays of the
	 * two HashableByteArray objects.
	 */
	@Override
	public boolean equals(Object o)
	{
		if(!(o instanceof HashableByteArray))
		{
			return false;
		}
		return Arrays.equals(this.data, ((HashableByteArray)o).data);
	}
	
	/**
	 * Compares this array to {@code other} using the following steps:
	 * <ol>
	 *   <li>Compare lengths: a shorter array is "less than" a longer array, regardless of values.</li>
	 *   <li>Compare values: the byte value in each array is compared, from first to last, and ordered by binary value.</li>
	 * </ol>
	 */
	@Override
	public int compareTo(HashableByteArray other)
	{
		if(this.data.length != other.data.length)
			return this.data.length - other.data.length;
		
		for(int i = 0; i < this.data.length; ++i)
		{
			if(this.data[i] != other.data[i])
				return (this.data[i]&0xFF) - (other.data[i]&0xFF);
		}
		return 0;
	}
	
	/**
	 * Prints this array as a hexadecimal string using {@link NumericUtils#toHexShortString(byte[])}.
	 */
	@Override
	public String toString()
	{
		return NumericUtils.toHexShortString(this.data);
	}
}
