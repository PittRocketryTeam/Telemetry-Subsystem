/**
 * Very stupid-simple message class.  By implementing the Serializble
 * interface, objects of this class can be serialized automatically by
 * Java to be sent across IO streams.  
 *
 * @author Adam J. Lee (adamlee@cs.pitt.edu) 
 *
 */
import java.math.BigInteger;
import java.nio.ByteBuffer; // for the float2byte[]

public class Message //implements java.io.Serializable
{
	//private static final long serialVersionUID = 3452098893656819551L;
	/** The text string encoded in this Message object */
	public String theMessage;
	private final byte[] mlen = new BigInteger(String.valueOf("128")).toByteArray();
	private final int messageIdLen = 32;
	private BigInteger messageId;
	private float value;
	private float value2;
	
	/**
	* Constructor.
	*
	* @param _msg The string to be encoded in this Message object
	*
	*/
	public Message(int _msgid)
	{
		setMsgId(_msgid);
	}

	public Message(int _msgid, float val, float val2)
	{
		setMsgId(_msgid);
		value = val;
		value2 = val2;
	}	
	
	public void setValue(float val)
	{
		value = val;
	}
	
	public void setValue2(float val)
	{
		value2 = val;
	}
	
	public void setMsgId(int id)
	{
		messageId = new BigInteger(String.valueOf(id));
	}
	
	public static byte [] float2ByteArray(float value)
	{  
	     return ByteBuffer.allocate(4).putFloat(value).array();
	}
	
	public byte[] getMessage()
	{
		byte[] retval = new byte[16];
		byte[] tempm = messageId.toByteArray();
		byte[] tempv1 = float2ByteArray(value);
		byte[] tempv2 = float2ByteArray(value2);
		
		retval[0] = mlen[0];
		retval[1] = mlen[1];
		retval[2] = mlen[2];
		retval[3] = mlen[3];
		
		retval[4] = tempm[4];
		retval[5] = tempm[5];
		retval[6] = tempm[6];
		retval[7] = tempm[7];
		
		retval[8] = tempv1[8];
		retval[9] = tempv1[9];
		retval[10] = tempv1[10];
		retval[11] = tempv1[11];
		
		retval[12] = tempv2[12];
		retval[13] = tempv2[13];
		retval[14] = tempv2[14];
		retval[15] = tempv2[15];
		
		return retval;
	}

}  //-- End class Message
