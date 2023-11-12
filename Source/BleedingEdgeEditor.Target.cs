using UnrealBuildTool;
using System.Collections.Generic;

public class BleedingEdgeEditorTarget : TargetRules
{
	public BleedingEdgeEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;

		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;


		ExtraModuleNames.AddRange(new[] { "BleedingEdge" });
	}
}