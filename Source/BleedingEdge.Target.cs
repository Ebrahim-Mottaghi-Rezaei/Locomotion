

using UnrealBuildTool;
using System.Collections.Generic;

public class BleedingEdgeTarget : TargetRules
{
	public BleedingEdgeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BleedingEdge" } );
	}
}
