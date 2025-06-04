# flasher.py
import subprocess
from pathlib import Path

# This is use f-multiline
def gen_script(hex_path: str) -> str:
    return f"""h
loadfile {hex_path}
r
g
exit
"""

# This is use join for 
def gen_script_2(hex_path: str) -> str:
    return "\n".join([
        "h",
        f"loadfile {hex_path}",
        "r",
        "g",
        "exit"
    ])

def flash_hex(hex_path: str) -> None:
    script = gen_script_2(hex_path)
    script_path = Path("flash.jlink")
    script_path.write_text(script)
    device="nRF52832_xxAA"
    
    cmd = [
        "JLink.exe",
        "-device", device,
        "-if", "SWD",
        "-speed", "4000",
        "-CommanderScript", str(script_path)
    ]
    
    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode != 0:
        print("❌ Flash failed:")
        print(result.stderr.decode())
    else:
        print("✅ Flash OK")

    # "w" writeover : remove old content, write new
    # "a" append : append new 
    # "w+" 
    # "r"
    with open("flash.log","w") as f:
        f.write(result.stdout)
        f.write(result.stderr)

    script_path.unlink(missing_ok=True)  # Xóa file tạm

