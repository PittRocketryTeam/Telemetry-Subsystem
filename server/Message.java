/**
 * Very stupid-simple message class.  By implementing the Serializble
 * interface, objects of this class can be serialized automatically by
 * Java to be sent across IO streams.  
 *
 * @author Adam J. Lee (adamlee@cs.pitt.edu) 
 *
 */
import java.math.BigInteger;

public class Message //implements java.io.Serializable
{
	//private static final long serialVersionUID = 3452098893656819551L;
	/** The text string encoded in this Message object */
	public String theMessage;
	private final int packetLen = 32;
	private final int messageIdLen = 32;
	private BigInteger messageId;
	private BigInteger value;
	private BigInteger value2;
	
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
	
	public void setValue(int val)
	{
		value = new BigInteger(String.valueOf(val));
	}
	
	public void setValue2(int val)
	{
		value2 = new BigInteger(String.valueOf(val));
	}
	
	public void setMsgId(int id)
	{
		messageId = new BigInteger(String.valueOf(id));
	}
	
	public byte[] getMessage()
	{
		byte[] retval = new byte[16];
		byte[] tempm = messageId.toByteArray();
		retval[0] = tempm[0];
		retval[1] = tempm[1];
		retval[2] = tempm[2];
		retval[3] = tempm[3];
		
		return retval;
	}

}  //-- End class Message
