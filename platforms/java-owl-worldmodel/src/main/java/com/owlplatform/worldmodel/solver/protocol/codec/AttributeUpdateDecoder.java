/*
 * Owl Platform World Model Library for Java
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
package com.owlplatform.worldmodel.solver.protocol.codec;

import org.apache.mina.core.buffer.IoBuffer;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.codec.ProtocolDecoderOutput;
import org.apache.mina.filter.codec.demux.MessageDecoder;
import org.apache.mina.filter.codec.demux.MessageDecoderResult;

import com.owlplatform.worldmodel.Attribute;
import com.owlplatform.worldmodel.solver.protocol.messages.AttributeUpdateMessage;


/**
 * Decoder for Attribute Update messages.
 * @author Robert Moore
 *
 */
public class AttributeUpdateDecoder implements MessageDecoder {

	@Override
	public MessageDecoderResult decodable(IoSession session, IoBuffer buffer) {
		if (buffer.prefixedDataAvailable(4, 65536)) {
			buffer.mark();
			int messageLength = buffer.getInt();
			if (messageLength < 1) {
				buffer.reset();
				return MessageDecoderResult.NOT_OK;
			}

			byte messageType = buffer.get();
			buffer.reset();
			if (messageType == AttributeUpdateMessage.MESSAGE_TYPE) {
				return MessageDecoderResult.OK;
			}
			return MessageDecoderResult.NOT_OK;
		}
		return MessageDecoderResult.NEED_DATA;
	}

	@Override
	public MessageDecoderResult decode(IoSession session, IoBuffer buffer,
			ProtocolDecoderOutput out) throws Exception {
		AttributeUpdateMessage message = new AttributeUpdateMessage();
		
		buffer.getInt();
		
		buffer.get();
		byte createIds = buffer.get();
		message.setCreateId(createIds == (byte)0? false : true);
		
		int numSolutions = buffer.getInt();
		Attribute[] attributes = new Attribute[numSolutions];
		for(int i = 0; i < numSolutions; ++i){
			Attribute attr = new Attribute();
			int attributeAlias = buffer.getInt();
			attr.setAttributeNameAlias(attributeAlias);
			
			long time = buffer.getLong();
			attr.setCreationDate(time);
			
			int idLength = buffer.getInt();
			byte[] idBytes = new byte[idLength];
			buffer.get(idBytes);
			attr.setId(new String(idBytes,"UTF-16BE"));
			
			int dataLength = buffer.getInt();
			byte[] data = new byte[dataLength];
			buffer.get(data);
			attr.setData(data);
			
			attributes[i] = attr;
		}
		
		out.write(message);
		
		return MessageDecoderResult.OK;
	}

	@Override
	public void finishDecode(IoSession arg0, ProtocolDecoderOutput arg1)
			throws Exception {
		// TODO Auto-generated method stub

	}

}
