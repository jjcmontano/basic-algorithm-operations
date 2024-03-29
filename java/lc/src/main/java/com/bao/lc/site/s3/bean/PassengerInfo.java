package com.bao.lc.site.s3.bean;

public class PassengerInfo
{
	public String cardNo; // 证件号码
	public String name;
	public String phone;

	public String cardType; // 证件类型: 二代身份证, 一代身份证
	public String tiketType; // 车票类型：成人票, 儿童票...
	public String seatClass; // 席别: 硬卧,软卧
	public String isSave; // 是否保存到常用联系人: Y, N

	public PassengerInfo()
	{
		this.cardType = "1";
		this.tiketType = "1";
		this.isSave = "Y";
	}

	public String getPassengerTickets()
	{
		StringBuilder sb = new StringBuilder();
		sb.append(seatClass).append(",").append(tiketType).append(",");
		sb.append(name).append(",").append(cardType).append(",").append(cardNo).append(",");
		sb.append(phone).append(",").append(isSave);
		return sb.toString();
	}

	public String getOldPassenger()
	{
		StringBuilder builder = new StringBuilder();
		builder.append(name).append(",").append(cardType).append(",").append(cardNo);
		return builder.toString();
	}
	
	public String saveToString()
	{
		StringBuilder sb = new StringBuilder();
		sb.append(name).append(",").append(cardType).append(",").append(cardNo);
		sb.append(",").append(tiketType).append(",").append(phone).append(",").append(isSave);
		return sb.toString();
	}
	
	public void loadFromString(String str)
	{
		if(str == null)
		{
			return;
		}
		String[] fields = str.split(",");
		for(int i = 0; i < fields.length; i++)
		{
			fields[i] = fields[i].trim();
		}
		
		if(fields.length < 6)
		{
			return;
		}
		
		int i = 0;
		name = fields[i++];
		cardType = fields[i++];
		cardNo = fields[i++];
		tiketType = fields[i++];
		phone = fields[i++];
		isSave = fields[i++];
	}
}
