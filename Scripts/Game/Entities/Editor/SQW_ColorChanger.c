[ComponentEditorProps(category: "GameScripted/ColorChanger", description: "Allows color Changing of shapes")]
class SQW_ColorChangerClass : ScriptComponentClass
{
}


//------------------------------------------------------------------------------------------------
class SQW_ColorChanger : ScriptComponent
{
	
	/*
	You totally can change materials via script, you can use ParametricMaterialInstanceComponent component 
	for basic emat attributes or if you want something a bit more advanced then you can use 
	SCR_CustomMaterialAnimatorEntity (check the docs of this entity in the file where it is defined at)
	or you can implement your own if you need a bit more control.
	All of these will change the material for a specific entity instance, so it's not global
	*/
	
	//location: X,Y,Z
	vector m_vOrigin = {60, 1, 70};
	
	//Replication
	[RplProp(onRplName: "OnColorChanged")]			// this value is to be updated by the authority, not set locally by proxies (even owner)
	protected int m_Color; 							// if it is set locally, the change will not broadcast and there will be a difference between the proxy and the authority
													// this state discrepancy will last until authority's next update broadcast
	 
	
	// Attached component.
	protected RplComponent m_pRplComponent;
	protected GenericEntity m_pCube;
	protected ref Shape m_Sphere;
	protected SQW_EditableCommentEntity m_pComment; 
	protected ref RandomGenerator m_pRandomGenerator;
	
	//HUD
	protected SCR_EditableCommentComponent m_NLoCTextBox;
	protected bool m_bNetLoadOnClient;
	protected SCR_EditableCommentComponent m_RplTextBox;
	protected bool m_bReplicated;
	protected SCR_EditableCommentComponent m_ColorTextBox;
	
	
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Authority_Method(bool turningOn)
	{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//------------------------------------------------------------------------------------------------
	// Called on the authority when an entity gets streamed
	override bool RplSave(ScriptBitWriter writer)
	{
		
		writer.Write(m_Color, 32);  //write 32 bits of m_Color - int is 32 bits in size
			
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	// Called on the streamed proxy
	override bool RplLoad(ScriptBitReader reader)
	{
	
		if (!reader.Read(m_Color, 32))  // read 32 bits of data - the authority wrote m_Color first, so it needs to be read first
		{
			return false;
		}
		
		m_Sphere = Shape.CreateSphere(m_Color, ShapeFlags.VISIBLE, m_vOrigin, 1);
		
		return true;
	}
	
	
	
	
	
	
	
	
	//------------------------------------------------------------------------------------------------
	protected void OnTriggerActivate()
	{			
		int color = GetRandomColor();
		m_Color = color;
		
		PrintFormat("New Color: %1", color.ToString());
		m_Sphere.SetColor(color);		
	}
	
	//------------------------------------------------------------------------------------------------
	// Gets Random color as int with 100% alpha
	int GetRandomColor()
	{
		if(!m_pRandomGenerator)
		{
			m_pRandomGenerator = new RandomGenerator();
		}
		
		//random 8bit color between 0x00000000 and 0xFFFFFFFF
		 int _color = 0xff000000 | Math.RandomIntInclusive(0x0,0xffffff);
	
		return _color;
	}
	
	
	
	//------------------------------------------------------------------------------------------------
	override void EOnInit(IEntity owner)
	{
			SCR_BaseTriggerEntity parentTrigger = SCR_BaseTriggerEntity.Cast(owner);
			if (!parentTrigger)
			{
				Print("SQW_ColorChanger cannot find trigger, it is not a child of SCR_BaseTriggerEntity!");
				return;
			}

			parentTrigger.GetOnActivate().Insert(OnTriggerActivate);	
	}
	
	
	//------------------------------------------------------------------------------------------------
	protected bool VerifyComponentsPresent()
	{
		//Check for rplComponent
		if (!m_pRplComponent)
		{
			Print("SQW_ColorChanger does not have a RplComponent attached!", LogLevel.ERROR);
			return false;
		}
		

		
		Print("Found everything!",LogLevel.WARNING);
		return true;
	}
	
	
	//------------------------------------------------------------------------------------------------
	override void OnPostInit(IEntity owner)
	{
		m_pRplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
					
		m_Sphere = Shape.CreateSphere(0xff000000, ShapeFlags.VISIBLE, m_vOrigin, 1);
		
		if (!VerifyComponentsPresent())
		return;

		SetEventMask(owner, EntityEvent.INIT);
	}

		
	//------------------------------------------------------------------------------------------------
	void SQW_ColorChanger(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}

	
	//------------------------------------------------------------------------------------------------
	void ~SQW_ColorChanger()
	{
	}

}

