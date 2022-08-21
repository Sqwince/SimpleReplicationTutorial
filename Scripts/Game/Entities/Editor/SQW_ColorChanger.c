[ComponentEditorProps(category: "GameScripted/ColorChanger", description: "Allows color Changing of shapes")]
class SQW_ColorChangerClass : ScriptComponentClass
{
}

//------------------------------------------------------------------------------------------------
/* SIMPLE REPLICATION IMPLEMENTATION TUTORIAL BASED ON THE FOLLOWING TUTORIALS:
	https://community.bistudio.com/wiki/Arma_Reforger:Multiplayer_Scripting
	https://www.youtube.com/watch?v=4Tnbf44NjXo&list=PLxwrIHk2cX5t4vQMdHDwtJvJ1ngACyyDO&index=7&t=320s
*/
//------------------------------------------------------------------------------------------------
class SQW_ColorChanger : ScriptComponent
{
	protected BaseWorld m_World;
	protected ref RandomGenerator m_pRandomGenerator;
	
	//Cube
	protected GameEntity m_Cube;
	ParametricMaterialInstanceComponent m_ParametricMaterialinstanceComponent;

	
	//Replication
	[RplProp(onRplName: "OnColorChanged")]				// m_Color: this value is to be updated by the authority, not set locally by proxies (even owner)
	protected int m_Color; 								// if it is set locally, the change will not broadcast and there will be a difference between the proxy and the authority
														// this state discrepancy will last until authority's next update broadcast

	
	
	// Attached component.
	protected RplComponent m_pRplComponent;

	
	
	//------------------------------------------------------------------------------------------------
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Authority_Method()
	{			
		Print("authority-side code");
		//Change Color
		m_Color = GetRandomColor();
		m_ParametricMaterialinstanceComponent.SetColor(m_Color);
		Replication.BumpMe();
	}
	
	//------------------------------------------------------------------------------------------------
	// T
	protected void OnColorChanged()
	{					
		//Change Color
		//m_Color = GetRandomColor();
		Print("proxy-side code");
		m_ParametricMaterialinstanceComponent.SetColor(m_Color);					
	}
	
	//------------------------------------------------------------------------------------------------
	protected void OnTriggerActivate()
	{					
		//Request Server Change Color		
		Rpc(RpcAsk_Authority_Method);
	}
	
	//------------------------------------------------------------------------------------------------
	// Gets Random color as int with 100% alpha
	protected int GetRandomColor()
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
	override void OnPostInit(IEntity owner)
	{				
		//world
		m_World = GetGame().GetWorld();
		if (!m_World)
		{
			Print("SQW_ColorChanger could not find World!", LogLevel.WARNING);
			return;
		}
			
		//Check for rplComponent
		m_pRplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		if (!m_pRplComponent)
		{
			Print("SQW_ColorChanger does not have a RplComponent attached!", LogLevel.ERROR);
			return;
		}
	
		//Attach to trigger
		SCR_BaseTriggerEntity parentTrigger = SCR_BaseTriggerEntity.Cast(owner);
		if (!parentTrigger)
		{
			Print("SQW_ColorChanger cannot find trigger, it is not a child of SCR_BaseTriggerEntity!");
			return;
		}

		parentTrigger.GetOnActivate().Insert(OnTriggerActivate);
		
		//Cube Object
		m_Cube = GameEntity.Cast(m_World.FindEntityByName("TheCube"));	
			
		if(!m_Cube)
			{
				Print("SQW_ColorChanger could not locate TheCube!", LogLevel.ERROR);
				return;
			}
		
		//cube material Component
		/*You can change materials via ParametricMaterialInstanceComponent component 
		  for basic emat attributes or if you want something a bit more advanced then you can use 
		  SCR_CustomMaterialAnimatorEntity (check the docs of this entity in the file where it is defined at)
		  or you can implement your own if you need a bit more control.
		  All of these will change the material for a specific entity instance, so it's not global
		*/
		m_ParametricMaterialinstanceComponent = ParametricMaterialInstanceComponent.Cast(m_Cube.FindComponent(ParametricMaterialInstanceComponent));
		
		if(!m_ParametricMaterialinstanceComponent)
			{
				Print("Cube needs to have ParametricMaterialInstanceComponent included", LogLevel.ERROR);
				return;
			}			
		
		//Init completed
		Print("Found everything!",LogLevel.WARNING);
		SetEventMask(owner, EntityEvent.INIT);
	}
		
	//------------------------------------------------------------------------------------------------
	//Constructor
	void SQW_ColorChanger(IEntityComponentSource src, IEntity ent, IEntity parent)
	{
	}
	
	//------------------------------------------------------------------------------------------------
	//Destructor
	void ~SQW_ColorChanger()
	{
	}

}

