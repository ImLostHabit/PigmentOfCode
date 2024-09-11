

using UnrealBuildTool;
using System.Collections.Generic;

public class PigmentOfFearTarget : TargetRules
{
	public PigmentOfFearTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange( new string[] { "PigmentOfFear" } );
	}
}
