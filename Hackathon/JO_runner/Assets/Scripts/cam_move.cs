using UnityEngine;
using System.Collections;
using System.Collections.Generic;
[AddComponentMenu("Camera-Control/Smooth Mouse Look")]
public class SmoothMouseLook : MonoBehaviour
{
    public float sensitivy = 5.0f;
    void Start()
    {
        Cursor.lockState = CursorLockMode.Locked;
    }
    void Update()
    {
        transform.eulerAngles += sensitivy * new Vector3( x: -Input.GetAxis("Mouse Y"), y: Input.GetAxis("Mouse X"), z: 0);
    }
}
