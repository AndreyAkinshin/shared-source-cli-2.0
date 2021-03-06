//------------------------------------------------------------------------------
// <copyright file="ComponentRenameEvent.cs" company="Microsoft">
//     
//      Copyright (c) 2006 Microsoft Corporation.  All rights reserved.
//     
//      The use and distribution terms for this software are contained in the file
//      named license.txt, which can be found in the root of this distribution.
//      By using this software in any fashion, you are agreeing to be bound by the
//      terms of this license.
//     
//      You must not remove this notice, or any other, from this software.
//     
// </copyright>                                                                
//------------------------------------------------------------------------------

/*
 */
namespace System.ComponentModel.Design {
    using Microsoft.Win32;
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Security.Permissions;

    /// <devdoc>
    /// <para>Provides data for the <see cref='System.ComponentModel.Design.IComponentChangeService.ComponentRename'/> event.</para>
    /// </devdoc>
    [HostProtection(SharedState = true)]
    [System.Runtime.InteropServices.ComVisible(true)]
    [System.Security.Permissions.PermissionSetAttribute(System.Security.Permissions.SecurityAction.InheritanceDemand, Name="FullTrust")]
    [System.Security.Permissions.PermissionSetAttribute(System.Security.Permissions.SecurityAction.LinkDemand, Name="FullTrust")]
    public class ComponentRenameEventArgs : EventArgs {
        private object component;
        private string oldName;
        private string newName;

        /// <devdoc>
        ///    <para>
        ///       Gets or sets the component that is being renamed.
        ///    </para>
        /// </devdoc>
        public object Component {
            get {
                return component;
            }
        }

        /// <devdoc>
        ///    <para>
        ///       Gets or
        ///       sets the name of the component before the rename.
        ///    </para>
        /// </devdoc>
        public virtual string OldName {
            get {
                return oldName;
            }
        }

        /// <devdoc>
        ///    <para>
        ///       Gets or
        ///       sets the current name of the component.
        ///    </para>
        /// </devdoc>
        public virtual string NewName {
            get {
                return newName;
            }
        }

        /// <devdoc>
        ///    <para>
        ///       Initializes a new instance of the <see cref='System.ComponentModel.Design.ComponentRenameEventArgs'/>
        ///       class.
        ///    </para>
        /// </devdoc>
        public ComponentRenameEventArgs(object component, string oldName, string newName) {
            this.oldName = oldName;
            this.newName = newName;
            this.component = component;
        }
    }
}
